// registerwidget.cpp
#include "registerwidget.h"
#include "ui_registerwidget.h"
#include "databaseconnection.h"  // 包含数据库连接类
#include <QSqlQuery>
#include <QSqlError>  // 添加这一行

registerwidget::registerwidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerwidget)
{
    ui->setupUi(this);

    // 连接注册按钮到槽
   // connect(ui->pushButton, &QPushButton::clicked, this, &registerwidget::on_pushButton_clicked);
}

registerwidget::~registerwidget()
{
    delete ui;
}

void registerwidget::on_pushButton_clicked()
{
    // 获取输入框的值
    QString username = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();

    // 获取数据库连接
    QSqlDatabase database = DatabaseConnection::getInstance().getDatabase();

    // 执行数据库插入
    QSqlQuery query(database);
    query.prepare("INSERT INTO user_info (name, password) VALUES (:username, :password)");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (query.exec()) {
        qDebug() << "注册成功。用户名：" << username << "密码：" << password;
        // 可选地，关闭注册对话框或显示成功消息
    } else {
        qDebug() << "注册失败。错误：" << query.lastError().text();
        // 处理注册失败，例如，显示错误消息
    }
}
