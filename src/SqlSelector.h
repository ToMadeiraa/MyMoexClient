#ifndef SQLSELECTOR_H
#define SQLSELECTOR_H

#include <QObject>
#include <QDebug>
#include <QDateTime>
#include <QMutex>

//#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QTimer>

class SqlSelector : public QObject
{
    Q_OBJECT
public:
    SqlSelector();

    //QSqlDatabase db;
    QSqlQuery* requestQuery;
    QMutex* mtx;

    QVector<double> *priceData;
    QVector<double> *timeData;
    long long int LastTradeno;

    void selectData(QString sec);

public slots:

};

#endif // SQLSELECTOR_H
