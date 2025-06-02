#ifndef EDITACCOUNT_H
#define EDITACCOUNT_H

#include <QDialog>

namespace Ui {
class editAccount;
}

class editAccount : public QDialog
{
    Q_OBJECT

public:
    explicit editAccount(QWidget *parent = nullptr);
    ~editAccount();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::editAccount *ui;
};

#endif // EDITACCOUNT_H
