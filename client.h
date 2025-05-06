// client.h
#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QMainWindow>
#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QThread>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include <QStandardPaths>
#include <QFile>
#include <QDir>
#include <QXmlStreamReader>

#include "SqlUpdater.h"
#include "PlotDrawer.h"

struct Version {
    ushort Major;
    ushort Minor;
    ushort Maintenance;

    Version() {
        Major = 0;
        Minor = 0;
        Maintenance = 0;
    }

    Version& operator=(const Version& v)
    {
        Major = v.Major;
        Minor = v.Minor;
        Maintenance = v.Maintenance;
        return *this;
    }

    void print() {
        qDebug() << QString("%1.%2.%3").arg(this->Major).arg(this->Minor).arg(this->Maintenance);
    }
};

namespace Ui {
class Client;
}

class Client : public QMainWindow
{
    Q_OBJECT
public:
    explicit Client(QWidget *parent = nullptr);
    ~Client();

    bool checkNewVersion();
    void update();

    QSqlDatabase db;
    QSqlQuery* requestQuery;
    QThread *sqlUpdaterThread;
    SqlUpdater *sqlUpdater;

    PlotDrawer *plotDrawer;

    Version ver;
    void readConfigFile();

private:
    QTcpSocket *socketUpdate;
    Ui::Client *ui;

private slots:
    void readyRead();
    void connected();
    void disconnected();

};

#endif // CLIENT_H
