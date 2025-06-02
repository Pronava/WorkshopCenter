#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QSqlDatabase>

class DatabaseConnection {
public:
    static DatabaseConnection& getInstance();
    QSqlDatabase getDatabase();

private:
    DatabaseConnection();  // 私有构造函数以防止实例化
    QSqlDatabase database;
};

#endif // DATABASECONNECTION_H
