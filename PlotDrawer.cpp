#include "PlotDrawer.h"

PlotDrawer::PlotDrawer(QCustomPlot* cp)
{
    this->customPlot = cp;

    time.resize(625*625);
    value.resize(625*625);

    // generate two sets of random walk data (one for candlestick and one for ohlc chart):
    start = QDateTime(QDate(2025, 5, 3), QTime(9,59,50));

    start.setTimeSpec(Qt::UTC);
    startTime = start.currentSecsSinceEpoch();

    qDebug() << startTime << "    START TIME";
    binSize = 60; // интервал в секундах

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
    dateTimeTicker->setDateTimeFormat("dd. MMMM hh:mm:ss");
    customPlot->xAxis->setTicker(dateTimeTicker);
    customPlot->xAxis->scaleRange(1.025, customPlot->xAxis->range().center());
    customPlot->yAxis->scaleRange(1.1, customPlot->yAxis->range().center());
    //customPlot->yAxis->setRange(60,70);
}

//1.74683e+09

void PlotDrawer::drawPlot()
{
    // for (int i=0; i<625*625; ++i) {
    //     time[i] = startTime+i;
    //     value[i] = i;
    // }
    //candlesticks->data()->set(QCPFinancial::timeSeriesToOhlc(time, value, binSize, startTime));


    candlesticks->data()->set(QCPFinancial::timeSeriesToOhlc(*timeData, *priceData, binSize, startTime));
    customPlot->rescaleAxes();
    customPlot->replot();
}
