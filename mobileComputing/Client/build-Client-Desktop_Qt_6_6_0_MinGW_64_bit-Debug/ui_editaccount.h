/********************************************************************************
** Form generated from reading UI file 'editaccount.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITACCOUNT_H
#define UI_EDITACCOUNT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_editAccount
{
public:
    QPushButton *pushButton_2;
    QLineEdit *lineEdit_2;
    QLabel *label_2;
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;

    void setupUi(QDialog *editAccount)
    {
        if (editAccount->objectName().isEmpty())
            editAccount->setObjectName("editAccount");
        editAccount->resize(541, 396);
        pushButton_2 = new QPushButton(editAccount);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(200, 310, 80, 24));
        lineEdit_2 = new QLineEdit(editAccount);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(200, 120, 113, 23));
        label_2 = new QLabel(editAccount);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(130, 80, 54, 16));
        pushButton = new QPushButton(editAccount);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(200, 170, 80, 24));
        lineEdit = new QLineEdit(editAccount);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(200, 70, 113, 23));
        label_3 = new QLabel(editAccount);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(130, 120, 54, 16));
        label_4 = new QLabel(editAccount);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(113, 260, 71, 20));
        label_5 = new QLabel(editAccount);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(113, 220, 71, 20));
        lineEdit_3 = new QLineEdit(editAccount);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(200, 260, 113, 23));
        lineEdit_4 = new QLineEdit(editAccount);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setGeometry(QRect(200, 210, 113, 23));

        retranslateUi(editAccount);

        QMetaObject::connectSlotsByName(editAccount);
    } // setupUi

    void retranslateUi(QDialog *editAccount)
    {
        editAccount->setWindowTitle(QCoreApplication::translate("editAccount", "Dialog", nullptr));
        pushButton_2->setText(QCoreApplication::translate("editAccount", "modify", nullptr));
        label_2->setText(QCoreApplication::translate("editAccount", "name", nullptr));
        pushButton->setText(QCoreApplication::translate("editAccount", "delete", nullptr));
        label_3->setText(QCoreApplication::translate("editAccount", "pwd", nullptr));
        label_4->setText(QCoreApplication::translate("editAccount", "new pwd", nullptr));
        label_5->setText(QCoreApplication::translate("editAccount", "new name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class editAccount: public Ui_editAccount {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITACCOUNT_H
