#include "SqlSelector.h"

SqlSelector::SqlSelector()
{
    LastTradeno = 1;
    timerSelectData = new QTimer;
    connect(timerSelectData, SIGNAL(timeout()), this, SLOT(selectData()));
    timerSelectData->start(100);
}

void SqlSelector::selectData()
{
    mtx->lock();

    QString reqString = "SELECT TRADENO, PRICE, SYSTIME FROM moex_client WHERE TRADENO > " + QString::number(LastTradeno) + " LIMIT 100;";
    if (LastTradeno == 0) return;

    requestQuery->exec(reqString);
    requestQuery->first();

    double dateTimeInSec;

    while (requestQuery->next()) {
        LastTradeno = requestQuery->value(0).toLongLong();
        priceData->push_back(requestQuery->value(1).toDouble());
        dateTimeInSec = requestQuery->value(2).toDouble();
        timeData->push_back(dateTimeInSec);
    }

    mtx->unlock();
}


