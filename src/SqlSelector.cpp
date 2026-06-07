#include "SqlSelector.h"

SqlSelector::SqlSelector()
{
}

void SqlSelector::selectData(QString sec)
{
    QString reqString = "SELECT PRICE, QUANTITY, SYSTIME, BUYSELL FROM " + sec + ";";

    requestQuery->exec(reqString);
    requestQuery->first();
    double dateTimeInSec = 0;
    do {
        if (dateTimeInSec > requestQuery->value(2).toDateTime().toSecsSinceEpoch())
            continue;

        dateTimeInSec = requestQuery->value(2).toDateTime().toSecsSinceEpoch();
        priceData->push_back(requestQuery->value(0).toDouble());
        quantityData->push_back(requestQuery->value(1).toUInt());
        timeData->push_back(requestQuery->value(2).toDateTime().toSecsSinceEpoch());
        buysellData->push_back(requestQuery->value(3).toBool());
    } while (requestQuery->next());
}


