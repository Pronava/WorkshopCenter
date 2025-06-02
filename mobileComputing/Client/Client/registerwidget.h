// registerwidget.h
#ifndef REGISTERWIDGET_H
#define REGISTERWIDGET_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
    class registerwidget;
}

class registerwidget : public QDialog
{
    Q_OBJECT

public:
    explicit registerwidget(QWidget *parent = nullptr);
    ~registerwidget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::registerwidget *ui;
};

#endif // REGISTERWIDGET_H
