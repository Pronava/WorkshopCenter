// server.cpp

#include "server.h"
#include "ui_server.h"
#include "databaseconnection.h"  // 包含数据库连接类
#include <QSqlQuery>
#include <QTcpSocket>
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>
#include <QDateTime> // 包含 QDateTime 头文件
#include <QString>

Server::Server(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &Server::startServer);
}

void Server::startServer()
{
    qint16 port = ui->lineEdit->text().toInt();
    if (port <= 0 || port > 65535) {
        QMessageBox::warning(this, "Invalid Port", "Please enter a valid port number.");
        return;
    }

    if (!tcpServer.listen(QHostAddress::Any, port)) {
        QMessageBox::critical(this, "Error", "Unable to start the server: " + tcpServer.errorString());
        return;
    }

    ui->textBrowser->append("Server started. Listening on port " + QString::number(port));
    connect(&tcpServer, &QTcpServer::newConnection, this, &Server::newConnection);
}

void Server::newConnection()
{
    while (tcpServer.hasPendingConnections()) {
        QTcpSocket *clientSocket = tcpServer.nextPendingConnection();
        QString currentDateTime = QDateTime::currentDateTime().toString(Qt::ISODate);
        clientConnectionTimes[clientSocket] = currentDateTime;
        ui->textBrowser->append("New connection from (IPv4Address): " + clientSocket->peerAddress().toString());
        connectedClients.append(clientSocket);
        connect(clientSocket, &QTcpSocket::readyRead, this, &Server::readClientData);
        qDebug() << "Client connected: " << clientSocket->peerAddress().toString();
        loadHistoricalRecords();
    }
}

void Server::loadHistoricalRecords()
{
    qDebug() << "call loadHistoricalRecords";
    QSqlDatabase database = DatabaseConnection::getInstance().getDatabase();
    QSqlQuery query(database);
    qint16 port = ui->lineEdit->text().toInt();
    query.prepare("SELECT chat_history.history FROM chat_history JOIN chat_group ON chat_history.room_id = chat_group.room_id WHERE chat_group.port = :port");
    query.bindValue(":port", port);

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        QString history = query.value(0).toString();
        sendFeedbackToAllClients(history);
    }
}

void Server::readClientData()
{
    for (QTcpSocket *clientSocket : connectedClients) {
        if (clientSocket->bytesAvailable() <= 0) {
            continue;
        }

        QDataStream in(clientSocket);
        in.setVersion(QDataStream::Qt_6_0);

        QString receivedMessage;
        in >> receivedMessage;

        QString clientIP = clientSocket->peerAddress().toString();
        QString connectionTime = clientConnectionTimes[clientSocket];
        receivedMessage.append("_").append(clientIP).append("_").append(connectionTime);

        qDebug() << "Received message from " << clientSocket->peerAddress().toString() << ": " << receivedMessage;

        sendFeedbackToAllClients(receivedMessage);
        ui->textBrowser->append("Received message from " + clientSocket->peerAddress().toString() + ": " + receivedMessage);

        QSqlDatabase database = DatabaseConnection::getInstance().getDatabase();
        QSqlQuery query(database);
        qint16 port = ui->lineEdit->text().toInt();
        query.prepare("UPDATE chat_history "
                      "SET history = CONCAT(history, ',', :receivedMessage) "
                      "WHERE room_id IN ("
                      "SELECT room_id "
                      "FROM chat_group "
                      "WHERE port = :port"
                      ");");
        query.bindValue(":port", port);
        query.bindValue(":receivedMessage", receivedMessage);

        qDebug() << "Query Text: " << query.lastQuery();

        if (!query.exec()) {
            qDebug() << "Error executing query:" << query.lastError().text();
            return;
        } else {
            qDebug() << "Inserted history";
        }
    }
}

void Server::sendFeedbackToAllClients(const QString &feedback)
{
    qDebug() << "call sendFeedbackToAllClients";
    for (QTcpSocket *clientSocket : connectedClients) {
        QDataStream out(clientSocket);
        out.setVersion(QDataStream::Qt_6_0);

        out << feedback;

        if (clientSocket->flush()) {
            qDebug() << "Sent feedback to " << clientSocket->peerAddress().toString() << ": " << feedback;
        } else {
            qDebug() << "Failed to send feedback to " << clientSocket->peerAddress().toString();
            // 这里可以添加错误处理逻辑
        }
    }
}
