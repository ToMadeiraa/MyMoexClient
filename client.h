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

#include "SqlUpdater.h"


class Client : public QWidget
{
    Q_OBJECT
public:
    explicit Client(QWidget *parent = nullptr);

    QSqlDatabase db;
    QSqlQuery* requestQuery;
    QHash<QString, long long int> LastTRADENOs;
    QHash<QString, ushort> SecID_Numbers;

    QThread *sqlUpdaterThread;
    SqlUpdater *sqlUpdater;

signals:
    void messageReceived(const QString &message);


private:
    QTcpSocket *socket;
};

#endif // CLIENT_H
