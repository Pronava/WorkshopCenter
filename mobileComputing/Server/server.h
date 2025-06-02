// server.h

#ifndef SERVER_H
#define SERVER_H

#include "ui_server.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QDataStream>

class Server : public QMainWindow
{
    Q_OBJECT

public:
    Server(QWidget *parent = nullptr);

public slots:
    void startServer();
    void newConnection();
    void readClientData();
    void sendFeedbackToAllClients(const QString &feedback);
    void loadHistoricalRecords();

private:
    Ui::Server *ui;
    QTcpServer tcpServer;
    QList<QTcpSocket*> connectedClients;
    QMap<QTcpSocket*, QString> clientConnectionTimes; // 修正为QString类型
    quint16 blockSize;
};

#endif // SERVER_H
