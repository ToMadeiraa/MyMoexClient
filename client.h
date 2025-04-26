// client.h
#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QThread>

class Client : public QWidget
{
    Q_OBJECT
public:
    explicit Client(QWidget *parent = nullptr);
    void connectToServer(const QString &host, quint16 port);
    void sendMessage(const QString &message);

signals:
    void messageReceived(const QString &message);

private slots:
    void readyRead();
    void connected();
    void disconnected();

private:
    QTcpSocket *socket;
};

#endif // CLIENT_H
