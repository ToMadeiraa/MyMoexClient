#include "PlotDrawer.h"

PlotDrawer::PlotDrawer(QCustomPlot* cp)
    : binSize(60)
    , autoRescale(true) //интервал в секундах
{
    this->customPlot = cp;

    // generate two sets of random walk data (one for candlestick and one for ohlc chart):
    start = QDateTime(QDate(2025, 5, 3), QTime(9,59,50));

    start.setTimeSpec(Qt::UTC);
    startTime = start.currentSecsSinceEpoch();

    // create candlestick chart:
    candlesticks = new QCPFinancial(customPlot->xAxis, customPlot->yAxis);
    candlesticks->setChartStyle(QCPFinancial::csCandlestick);
    candlesticks->setWidth(binSize*0.9); //расстояния между свечками
    candlesticks->setTwoColored(true);
    candlesticks->setBrushPositive(QColor(0, 215, 0));
    candlesticks->setBrushNegative(QColor(240, 0, 0));
    candlesticks->setPenPositive(QPen(QColor(0, 0, 0)));
    candlesticks->setPenNegative(QPen(QColor(0, 0, 0)));

    // configure axes of both main and bottom axis rect:
    QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
    dateTimeTicker->setDateTimeSpec(Qt::UTC);
    dateTimeTicker->setDateTimeFormat("dd. MMMM. yyyy hh:mm:ss");
    customPlot->xAxis->setTicker(dateTimeTicker);
    customPlot->xAxis->scaleRange(1.025, customPlot->xAxis->range().center());
    customPlot->yAxis->scaleRange(1.1, customPlot->yAxis->range().center());
    customPlot->xAxis->setRange(QCPRange(startTime, startTime+60));
    //customPlot->yAxis->setRange(60,70);
    //QCPRange range = customPlot->yAxis->range();
    //customPlot->setInteraction(QCP::iRangeZoom);
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iSelectAxes);
}


void PlotDrawer::drawPlot()
{
    candlesticks->data()->set(QCPFinancial::timeSeriesToOhlc(*timeData, *priceData, binSize, startTime));

    if (autoRescale) customPlot->rescaleAxes();
    customPlot->replot();
}

void PlotDrawer::setNewRange(QWheelEvent* e)
{
    QCPRange range = customPlot->xAxis->range();
    double lower_tmp = range.lower;
    double upper_tmp = range.upper;

    if (e->angleDelta().y() < 0) //отдалить
    {
        lower_tmp-=100;
        upper_tmp+=100;
    }
    else //приблизить
    {
        lower_tmp+=100;
        upper_tmp-=100;
    }
    customPlot->xAxis->setRange(lower_tmp,upper_tmp);
    customPlot->replot();
}

void PlotDrawer::setNewRangeX()
{
    qDebug() << "XXXXXX";
}
