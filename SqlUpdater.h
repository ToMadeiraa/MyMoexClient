#ifndef SQLUPDATER_H
#define SQLUPDATER_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QThread>
//#include <QTimer>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include <QDir>
#include <QHash>

class SqlUpdater : public QObject
{
    Q_OBJECT
public:
    SqlUpdater();
    void connectToServer(const QString &host, quint16 port);
    void sendLastTradeno();

    QSqlDatabase db;
    QSqlQuery* requestQuery;

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;
    QHash<QString, long long int> LastTRADENOs;
    QHash<QString, ushort> SecID_Numbers;
    long long int secsBefore2000;

public slots:
    void process();

private slots:
    void readyRead();
    void connected();
    void disconnected();

signals:
    void finished();
};

#endif // SQLUPDATER_H
