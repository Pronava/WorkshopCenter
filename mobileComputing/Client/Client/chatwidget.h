// chatwidget.h

#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QDialog>
#include <QTcpSocket>

namespace Ui {
class chatwidget;
}

class chatwidget : public QDialog
{
    Q_OBJECT

public:
    QString m_username;
    void setUserName(const QString &username);
    QString getUserName() const;
    void onSendMessageButtonClicked();
    bool insertChatGroup(const QString &group, qint64 port, qint64 room_id, int states);
    qint64 generateUniquePort();
    qint64 generateUniqueRoomId();
    bool groupExists(const QString &group);
    explicit chatwidget(const QString& username, QWidget *parent = nullptr);
    ~chatwidget();

private slots:
    void connectToServer();
    void disconnectFromServer();
    void readServerData();
    void on_pushButton_2_clicked();

/*protected:
    void closeEvent(QCloseEvent *event) override;*/

private:
    Ui::chatwidget *ui;
    QTcpSocket *tcpSocket;
    void receiveMessage();
    void populateChatGroups();
};

#endif // CHATWIDGET_H
