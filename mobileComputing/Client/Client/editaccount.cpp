#include "editaccount.h"
#include "ui_editaccount.h"
#include "databaseconnection.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

editAccount::editAccount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editAccount)
{
    ui->setupUi(this);

    // 初始化数据库连接
    QSqlDatabase database = DatabaseConnection::getInstance().getDatabase();
    // 检查数据库是否成功打开
    if (!database.isOpen()) {
        qDebug() << "数据库未成功打开。";
    }
}

editAccount::~editAccount()
{
    delete ui;
}

void editAccount::on_pushButton_clicked()
{
    QString name = ui->lineEdit->text();  // Assuming lineEdit is for name
    QString pwd = ui->lineEdit_2->text(); // Assuming lineEdit_2 is for password

    QSqlQuery query;
    query.prepare("DELETE FROM user_info WHERE name = :name AND password = :pwd");
    query.bindValue(":name", name);
    query.bindValue(":pwd", pwd);

    if(query.exec()) {
        QMessageBox::information(this, "删除成功", "账户已成功删除。");
    } else {
        QMessageBox::critical(this, "删除失败", "删除账户时出错: " + query.lastError().text());
    }
}

void editAccount::on_pushButton_2_clicked()
{
    QString name = ui->lineEdit->text();        // 当前用户名
    QString pwd = ui->lineEdit_2->text();       // 当前密码
    QString newName = ui->lineEdit_4->text();   // 新用户名
    QString newPwd = ui->lineEdit_3->text();    // 新密码

    // 检查新用户名是否已存在
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM user_info WHERE name = :newName");
    checkQuery.bindValue(":newName", newName);

    if (checkQuery.exec()) {
        if (checkQuery.next() && checkQuery.value(0).toInt() > 0) {
            QMessageBox::warning(this, "用户名冲突", "新用户名已存在，请选择不同的用户名。");
            return;
        }
    } else {
        QMessageBox::critical(this, "查询错误", "查询时出错:" + checkQuery.lastError().text());
        return;
    }

    // 更新账户信息
    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE user_info SET name = :newName, password = :newPwd WHERE name = :name AND password = :pwd");
    updateQuery.bindValue(":newName", newName);
    updateQuery.bindValue(":newPwd", newPwd);
    updateQuery.bindValue(":name", name);
    updateQuery.bindValue(":pwd", pwd);

    if(updateQuery.exec()) {
        QMessageBox::information(this, "更新成功", "账户信息已成功更新。");
    } else {
        QMessageBox::critical(this, "更新失败", "更新账户信息时出错:" + updateQuery.lastError().text());
    }
}
