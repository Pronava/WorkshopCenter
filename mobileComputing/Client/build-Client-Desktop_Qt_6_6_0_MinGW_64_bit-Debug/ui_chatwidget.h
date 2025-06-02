/********************************************************************************
** Form generated from reading UI file 'chatwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATWIDGET_H
#define UI_CHATWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_chatwidget
{
public:
    QTextBrowser *textBrowser;
    QTextEdit *textEdit;
    QPushButton *pushButton;
    QListWidget *listWidget;
    QLineEdit *lineEdit;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;

    void setupUi(QDialog *chatwidget)
    {
        if (chatwidget->objectName().isEmpty())
            chatwidget->setObjectName("chatwidget");
        chatwidget->resize(565, 436);
        textBrowser = new QTextBrowser(chatwidget);
        textBrowser->setObjectName("textBrowser");
        textBrowser->setGeometry(QRect(40, 41, 256, 221));
        textEdit = new QTextEdit(chatwidget);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(50, 280, 141, 70));
        pushButton = new QPushButton(chatwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(210, 300, 81, 41));
        listWidget = new QListWidget(chatwidget);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(360, 40, 141, 271));
        lineEdit = new QLineEdit(chatwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(370, 330, 113, 23));
        pushButton_2 = new QPushButton(chatwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(380, 370, 81, 41));
        lineEdit_2 = new QLineEdit(chatwidget);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(52, 380, 131, 23));
        pushButton_3 = new QPushButton(chatwidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(210, 370, 80, 24));
        pushButton_4 = new QPushButton(chatwidget);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(210, 400, 80, 24));

        retranslateUi(chatwidget);

        QMetaObject::connectSlotsByName(chatwidget);
    } // setupUi

    void retranslateUi(QDialog *chatwidget)
    {
        chatwidget->setWindowTitle(QCoreApplication::translate("chatwidget", "Dialog", nullptr));
        pushButton->setText(QCoreApplication::translate("chatwidget", "send", nullptr));
        pushButton_2->setText(QCoreApplication::translate("chatwidget", "add", nullptr));
        pushButton_3->setText(QCoreApplication::translate("chatwidget", "connect", nullptr));
        pushButton_4->setText(QCoreApplication::translate("chatwidget", "disconnect", nullptr));
    } // retranslateUi

};

namespace Ui {
    class chatwidget: public Ui_chatwidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATWIDGET_H
