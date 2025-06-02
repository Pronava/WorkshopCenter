// server.h

#ifndef SERVER_H
#define SERVER_H

#include <QDialog>
#include <QTcpServer>

namespace Ui {
class Server;
}

class Server : public QDialog
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = nullptr);
    ~Server();

private slots:
               // Add any other slots as needed

private:
    Ui::Server *ui;

    bool checkDatabaseStateAndPort();
    bool isPortAvailable(int port);
};

#endif // SERVER_H
