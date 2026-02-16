#include "SqlSelector.h"

SqlSelector::SqlSelector() :
    LastTradeno(0)
{
}

void SqlSelector::selectData(QString sec)
{
    QString reqString = "SELECT TRADENO, PRICE, SYSTIME FROM " + sec + " WHERE TRADENO > " + QString::number(LastTradeno) + ";";

    requestQuery->exec(reqString);
    requestQuery->first();

    double dateTimeInSec = 0;

    do {
        if (dateTimeInSec > requestQuery->value(2).toDateTime().toSecsSinceEpoch()) continue;
        dateTimeInSec = requestQuery->value(2).toDateTime().toSecsSinceEpoch();
        priceData->push_back(requestQuery->value(1).toDouble());
        timeData->push_back(dateTimeInSec);
    } while (requestQuery->next());
}


