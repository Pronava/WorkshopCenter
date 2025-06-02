#include "databaseconnection.h"
#include <QDebug>
#include <QSqlError>  // Include this line for QSqlError

DatabaseConnection::DatabaseConnection() {
    // 初始化数据库
    database = QSqlDatabase::addDatabase("QODBC");
    database.setHostName("localhost");
    database.setPort(3307);
    database.setDatabaseName("network");
    database.setUserName("root");
    database.setPassword("root");

    if (!database.open()) {
        qDebug() << "Failed to open database:" << database.lastError().text();
    }
}

DatabaseConnection& DatabaseConnection::getInstance() {
    static DatabaseConnection instance;  // 在程序结束时保证销毁
    return instance;
}

QSqlDatabase DatabaseConnection::getDatabase() {
    return database;
}
