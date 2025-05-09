#ifndef SQLSELECTOR_H
#define SQLSELECTOR_H

#include <QObject>
#include <QDebug>
#include <QDateTime>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QTimer>

class SqlSelector : public QObject
{
    Q_OBJECT
public:
    SqlSelector();

    QSqlDatabase db;
    QSqlQuery* requestQuery;
    QTimer* timerSelectData;

    QVector<double> *priceData;
    QVector<double> *timeData;
    long long int LastTradeno;

public slots:
    void selectData();

};

#endif // SQLSELECTOR_H
