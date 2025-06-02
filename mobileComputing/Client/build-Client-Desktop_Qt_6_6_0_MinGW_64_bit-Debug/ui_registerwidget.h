/********************************************************************************
** Form generated from reading UI file 'registerwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERWIDGET_H
#define UI_REGISTERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_registerwidget
{
public:
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QLineEdit *lineEdit_2;

    void setupUi(QDialog *registerwidget)
    {
        if (registerwidget->objectName().isEmpty())
            registerwidget->setObjectName("registerwidget");
        registerwidget->resize(400, 300);
        label_3 = new QLabel(registerwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(60, 140, 54, 16));
        label_2 = new QLabel(registerwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(60, 80, 54, 16));
        label = new QLabel(registerwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(160, 20, 54, 16));
        lineEdit = new QLineEdit(registerwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(130, 70, 113, 23));
        pushButton = new QPushButton(registerwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(130, 200, 80, 24));
        lineEdit_2 = new QLineEdit(registerwidget);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(130, 140, 113, 23));

        retranslateUi(registerwidget);

        QMetaObject::connectSlotsByName(registerwidget);
    } // setupUi

    void retranslateUi(QDialog *registerwidget)
    {
        registerwidget->setWindowTitle(QCoreApplication::translate("registerwidget", "Dialog", nullptr));
        label_3->setText(QCoreApplication::translate("registerwidget", "pwd", nullptr));
        label_2->setText(QCoreApplication::translate("registerwidget", "name", nullptr));
        label->setText(QCoreApplication::translate("registerwidget", "rgt", nullptr));
        pushButton->setText(QCoreApplication::translate("registerwidget", "confirm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class registerwidget: public Ui_registerwidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERWIDGET_H
