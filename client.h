// client.h
#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QThread>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QStandardPaths>
#include <QDir>
#include <QHash>


class Client : public QWidget
{
    Q_OBJECT
public:
    explicit Client(QWidget *parent = nullptr);
    void connectToServer(const QString &host, quint16 port);
    void sendLastTradeno();

    QSqlDatabase db;
    QSqlQuery* requestQuery;
    long long int LastTradeno;
    QHash<QString, long long int> LastTRADENOs;
    QHash<QString, ushort> SecID_Numbers;

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
