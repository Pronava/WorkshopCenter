#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QSqlDatabase>  // Add this line

QT_BEGIN_NAMESPACE
namespace Ui { class Client; }
QT_END_NAMESPACE

class Client : public QMainWindow
{
    Q_OBJECT

signals:
    void userLoggedIn(const QString& username);

public:
    Client(QWidget *parent = nullptr);
    ~Client();

private:
    QSqlDatabase database;  // Move the declaration to the private section

private slots:
    void on_pushButton_clicked();
    bool databaseValidation(const QString &username, const QString &password);
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Client *ui;
};
#endif // CLIENT_H
