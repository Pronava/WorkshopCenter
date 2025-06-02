#include "server.h"
#include "ui_server.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QTcpServer>
#include "databaseconnection.h"  // 请确保引入了数据库连接的头文件

Server::Server(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);

    // 在构造函数中检查数据库状态和端口
    if (checkDatabaseStateAndPort()) {
        // 根据需要在这里启动服务器
        // ...
    }
}

Server::~Server()
{
    delete ui;
}

bool Server::checkDatabaseStateAndPort()
{
    // 连接到数据库
    QSqlDatabase db = DatabaseConnection::getInstance().getDatabase();

    if (!db.isOpen()) {
        if (!db.open()) {
            qDebug() << "Failed to open database:" << db.lastError().text();
            return false;
        }
    }

    // 执行查询获取状态和端口
    QSqlQuery query(db);
    query.prepare("SELECT state, port FROM your_table WHERE your_condition");
    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError().text();
        qDebug() << "Query string:" << query.lastQuery();
        db.close();
        return false;
    }

    // 处理查询结果
    if (query.next()) {
        int state = query.value("state").toInt();
        int port = query.value("port").toInt();

        // 根据状态和端口的值判断是否需要启动服务器
        // 在这里添加你的逻辑
        if (state == 0 && isPortAvailable(port)) {
            // 重新生成端口，更新数据库，并启动服务器
            // ...
            return true;
        } else if (state > 0) {
            // 不需要重新启动服务器
            // ...
            return true;
        }
    }

    db.close();
    return false;
}

bool isPortAvailable(int port)
{
    QTcpServer server;
    return server.listen(QHostAddress::Any, port);
}

