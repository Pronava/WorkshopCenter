#include "ui_chatwidget.h"
#include "chatwidget.h"
#include <QCloseEvent>
#include "CustomWidgetItem.h"
#include "databaseconnection.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDataStream>

chatwidget::chatwidget(const QString& username, QWidget *parent)
    : QDialog(parent), m_username(username),
    ui(new Ui::chatwidget)
{
    ui->setupUi(this);
    tcpSocket = new QTcpSocket(this);
    populateChatGroups();

    connect(ui->pushButton_3, &QPushButton::clicked, this, &chatwidget::connectToServer);
    connect(ui->pushButton, &QPushButton::clicked, this, &chatwidget::onSendMessageButtonClicked);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &chatwidget::readServerData);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &chatwidget::disconnectFromServer);

    setUserName(username);
    qDebug() << "m_Username: " <<m_username;
}

/*void chatwidget::closeEvent(QCloseEvent *event)
{
    // 阻止窗口的默认关闭行为
    event->ignore();

    // 隐藏窗口，而不是关闭
    this->hide();
}*/
chatwidget::~chatwidget()
{
    delete ui;
}

void chatwidget::setUserName(const QString &username) {
    // 设置用户名
    m_username = username;
}
QString chatwidget::getUserName() const {
    return m_username;
}

void chatwidget::connectToServer()
{
    bool ok;
    int port = ui->lineEdit_2->text().toInt(&ok);

    if (!ok) {
        QMessageBox::critical(this, "Error", "Invalid port number.");
        return;
    }

    tcpSocket->connectToHost(QHostAddress::LocalHost, port);

    if (!tcpSocket->waitForConnected()) {
        QMessageBox::critical(this, "Error", "Failed to connect to the server.");
        return;
    }

    qDebug() << "Connected to the server!";
    // Perform other actions upon successful connection.
}

void chatwidget::disconnectFromServer()
{
    ui->textBrowser->clear();
    // 在这里执行断开与服务器的操作
    if (tcpSocket->state() == QAbstractSocket::ConnectedState) {
        tcpSocket->disconnectFromHost();
        tcpSocket->waitForDisconnected(); // 等待连接断开
        qDebug() << "Disconnected from the server!";
    }
}

void chatwidget::onSendMessageButtonClicked()
{
    QString message = ui->textEdit->toPlainText();

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);
    out << message;

    qint64 bytesWritten = tcpSocket->write(block);

    if (bytesWritten == -1) {
        qDebug() << "Failed to write data. Error:" << tcpSocket->errorString();
        return;
    }

    qDebug() << "Message sent successfully!";

}

void chatwidget::readServerData()
{
    qDebug() << "call readServerDatas";

    // Read data from the server
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_6_0);

    QString serverData;
    in >> serverData;

    qDebug() << "Received server data:" << serverData;

    // 显示接收到的数据
    ui->textBrowser->append(serverData);
}



/*void chatwidget::serverDisconnected()
{

}*/

void chatwidget::populateChatGroups()
{
    // Connect to the database
    QSqlDatabase database = DatabaseConnection::getInstance().getDatabase();

    if (!database.isOpen()) {
        if (!database.open()) {
            qDebug() << "Failed to open database:" << database.lastError().text();
            return;
        }
    }

    QSqlQuery query(database);
    query.prepare("SELECT * FROM chat_group WHERE `group` LIKE :username");
    query.bindValue(":username", "%" + m_username + "%");

    if (query.exec()) {
        ui->listWidget->clear();

        while (query.next()) {
            RoomInfo roomInfo;
            roomInfo.room_id = query.value("room_id").toString();
            roomInfo.port = query.value("port").toInt();
            roomInfo.state = query.value("states").toInt();
            roomInfo.group = query.value("group").toString();

            // 合并信息成为一个字符串
            QString displayText = "room " +roomInfo.room_id + ", port " +
                                  QString::number(roomInfo.port) + ", state " +
                                  QString::number(roomInfo.state) + ", group " +
                                  roomInfo.group;

            // 创建一个项目，并将 roomInfo 存储为 QVariant
            QListWidgetItem *item = new QListWidgetItem(displayText);
            QVariant data;
            data.setValue(roomInfo);
            item->setData(Qt::UserRole, data);

            // 将项目添加到列表
            ui->listWidget->addItem(item);
        }

    } else {
        qDebug() << "Query failed:" << query.lastError().text();
        qDebug() << "Query string:" << query.lastQuery();
    }

    database.close();
}

void chatwidget::on_pushButton_2_clicked()
{
    // 获取用户输入的聊天群组名
    QString userGroup = ui->lineEdit->text();

    // 生成唯一的 group，这里简单地将 m_username 与用户输入的群组名拼接起来
    QString group = m_username + "," + userGroup;

    if (groupExists(group)) {
        qDebug() << "Chat group already exists!";
        // Show a warning or handle it as needed
        return;
    }

    // 生成唯一的 port
    qint64 port;
    port = generateUniquePort();

    // 生成唯一的 room_id
    qint64 room_id;
    room_id = generateUniqueRoomId();

    // 默认 states 为 0
    int states = 0;

    // 将数据插入到数据库中
    if (insertChatGroup(group, port, room_id, states)) {
        populateChatGroups();
    }
}
bool chatwidget::groupExists(const QString &group)
{
    QSqlDatabase database = DatabaseConnection::getInstance().getDatabase();
    if (!database.isOpen()) {
        if (!database.open()) {
            qDebug() << "Failed to open database:" << database.lastError().text();
            return -1;
        }
    }
    // Check if the group exists in the chat_group table
    QSqlQuery query(database);
    query.prepare("SELECT COUNT(*) FROM chat_group WHERE `group` = :group");
    query.bindValue(":group", group);

    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();

        // If count is greater than 0, the group already exists
        return count > 0;
    } else {
        qDebug() << "Failed to query database:" << query.lastError().text();
        // Handle the error or return an appropriate value
        return false;
    }
}

qint64 chatwidget::generateUniquePort()
{
    QSqlDatabase database = DatabaseConnection::getInstance().getDatabase();
    if (!database.isOpen()) {
        if (!database.open()) {
            qDebug() << "Failed to open database:" << database.lastError().text();
            return -1;
        }
    }
    qint64 port = 1; // 起始端口
    const qint64 maxPort = 10000; // 最大端口

    while (port <= maxPort) {
        // 检查端口是否存在
        QSqlQuery query(database);
        query.prepare("SELECT COUNT(*) FROM chat_group WHERE port = :port");
        query.bindValue(":port", port);

        if (query.exec() && query.next()) {
            int count = query.value(0).toInt();

            if (count == 0) {
                // 端口不存在，返回该端口
                return port;
            }
        } else {
            qDebug() << "Failed to query database:" << query.lastError().text();
            return -1; // 返回错误值或采取其他处理方式
        }

        // 继续下一个端口
        port++;
    }

    qDebug() << "Failed to find unique port.";
    return -1; // 返回错误值或采取其他处理方式
}

qint64 chatwidget::generateUniqueRoomId()
{
    QSqlDatabase database = DatabaseConnection::getInstance().getDatabase();
    if (!database.isOpen()) {
        if (!database.open()) {
            qDebug() << "Failed to open database:" << database.lastError().text();
            return -1;
        }
    }
    qint64 roomId = 1; // 起始房间号
    const qint64 maxRoomId = 10000; // 最大房间号

    while (roomId <= maxRoomId) {
        // 检查房间号是否存在
        QSqlQuery query(database);
        query.prepare("SELECT COUNT(*) FROM chat_group WHERE room_id = :roomId");
        query.bindValue(":roomId", roomId);

        if (query.exec() && query.next()) {
            int count = query.value(0).toInt();

            if (count == 0) {
                // 房间号不存在，返回该房间号
                return roomId;
            }
        } else {
            qDebug() << "Failed to query database:" << query.lastError().text();
            return -1; // 返回错误值或采取其他处理方式
        }

        // 继续下一个房间号
        roomId++;
    }

    qDebug() << "Failed to find unique room_id.";
    return -1; // 返回错误值或采取其他处理方式
}

bool chatwidget::insertChatGroup(const QString &group, qint64 port, qint64 room_id, int states)
{
    // 连接到数据库
    QSqlDatabase database = DatabaseConnection::getInstance().getDatabase();

    // 检查数据库是否打开
    if (!database.isOpen()) {
        if (!database.open()) {
            qDebug() << "Failed to open database:" << database.lastError().text();
            return false;
        }
    }else {
        qDebug() << "Database opened successfully.";
    }

    // 准备插入数据的 SQL 语句
    QSqlQuery query(database);
    query.prepare("INSERT INTO chat_group (`group`, port, room_id, states) "
                  "VALUES (:group, :port, :room_id, :states)");

    // 绑定参数
    query.bindValue(":group", group);
    query.bindValue(":port", port);
    query.bindValue(":room_id", room_id);
    query.bindValue(":states", states);

    qDebug() << "SQL Query:" << query.lastQuery();

    // 执行插入操作
    if (query.exec()) {
        // 插入成功
        qDebug() << "Chat group inserted successfully!";
        return true;
    } else {
        // 插入失败
        qDebug() << "Failed to execute query:" << query.lastError().text();
        return false;
    }
}
