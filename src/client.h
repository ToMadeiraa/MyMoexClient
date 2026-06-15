// client.h
#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QMainWindow>
#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QThread>
#include <QMutex>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include <QStandardPaths>
#include <QFile>
#include <QDir>
#include <QXmlStreamReader>
#include <QTimer>
#include <QWheelEvent>

#include <QSplitter>
#include <QGridLayout>

#include "SqlUpdater.h"
#include "SqlSelector.h"
#include "topwidget.h"
#include "leftwidget.h"
#include "plotsdrawer.h"
#include "additionalplotdrawer.h"

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

    void print()
    {
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
    QMutex mtx;

    QThread *sqlUpdaterThread;
    SqlUpdater *sqlUpdater;

    QThread *sqlSelectorThread;
    SqlSelector *sqlSelector;

    QVector<double> priceData;
    QVector<double> timeData;
    QVector<uint>   quantityData;
    QVector<bool>   buysellData;

    QGridLayout             *p_topLeftGridLayout;
    QSplitter               *p_mainSplitter;
    QSplitter               *p_leftSplitter;
    QWidget                 *p_leftTopWidget;
    QWidget                 *p_leftBottomWidget;
    QWidget                 *p_rightWidget;
    PlotsDrawer             *plotsDrawer;
    AdditionalPlotDrawer    *p_additionalPlotDrawer;
    LeftWidget              *p_lw;
    TopWidget               *p_tw;


    Version ver;
    void readConfigFile();

private:
    void connectSlots();
    QTcpSocket *socketUpdate;
    Ui::Client *ui;


private slots:
    void readyRead();
    void connected();
    void disconnected();
    void redrawPlotBySecurityChange_slot();

};

#endif // CLIENT_H
