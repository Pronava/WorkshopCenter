// client.cpp
#include "client.h"
#include "ui_client.h"
#include "chatwidget.h"
#include "registerwidget.h"
#include "chatwidget.h"
#include "editaccount.h"
#include "databaseconnection.h"  // 包含数据库连接类
#include <QSqlQuery>
#include <QSqlError>  // 添加这一行
#include <QDebug>

Client::Client(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Client)
{
    ui->setupUi(this);

    // 初始化数据库连接
    database = DatabaseConnection::getInstance().getDatabase();
    // 检查数据库是否成功打开
    if (!database.isOpen()) {
        qDebug() << "数据库未成功打开。";
    }

}

Client::~Client()
{
    delete ui;
}

void Client::on_pushButton_clicked()
{
    qDebug() << "Login button clicked.";
    QString username = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();

    if (databaseValidation(username, password)) {
        // 如果验证成功，打开聊天窗口
        // 在需要的地方创建 chatwidget 的实例
        chatwidget *chatWidget = new chatwidget(username);
        chatWidget->show();

    } else {
        qDebug() << "登录失败。无效的用户名或密码。";
    }
}

void Client::on_pushButton_2_clicked()
{
    qDebug() << "Register button clicked.";
    // 打开注册窗口
    registerwidget *registerWidget = new registerwidget(this);
    registerWidget->show();
}

bool Client::databaseValidation(const QString &username, const QString &password)
{
    // 检查数据库是否打开
    /*if (!database.isOpen()) {
        qDebug() << "数据库未打开。";
        return false;
    }*/

    // 在这里执行数据库验证
    QSqlQuery query(database);
    query.prepare("SELECT * FROM user_info WHERE name = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (query.exec() && query.next()) {
        // 用户名和密码有效
        qDebug() << "登录成功。用户名：" << username << "密码：" << password;
        emit userLoggedIn(username);

        database.close();

        return true;
    } else {
        // 无效的用户名或密码
        qDebug() << "登录失败。无效的用户名或密码。用户名：" << username << "密码：" << password;
        return false;
    }
}

void Client::on_pushButton_3_clicked()
{
    qDebug() << "edit button clicked.";
    // 打开注册窗口
    editAccount *editaccount = new editAccount(this);
    editaccount->show();
}

