#include "PlotDrawer.h"

PlotDrawer::PlotDrawer(QCustomPlot* cp)
    : binSize(60) //интервал в секундах
    , autoRescale(true)
    , isXAxisChosen(false)
    , isYAxisChosen(false)
{

    this->customPlot = cp;

    start = QDateTime(QDate(2026, 1, 1), QTime(9,59,50));

    start.setTimeSpec(Qt::UTC);
    startTime = start.currentSecsSinceEpoch();

    candlesticks = new QCPFinancial(customPlot->xAxis, customPlot->yAxis2);

    candlesticks->setChartStyle(QCPFinancial::csCandlestick);
    candlesticks->setWidth(binSize*0.8); //расстояния между свечками
    candlesticks->setTwoColored(true);
    candlesticks->setBrushPositive(QColor(0, 215, 0));
    candlesticks->setBrushNegative(QColor(240, 0, 0));

    QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
    dateTimeTicker->setDateTimeSpec(Qt::UTC);
    dateTimeTicker->setDateTimeFormat("dd. MM. yyyy\n hh:mm:ss");
    customPlot->xAxis->setTicker(dateTimeTicker);
    customPlot->xAxis->setRange(QCPRange(startTime, startTime+60));
    customPlot->xAxis->scaleRange(1.025, customPlot->xAxis->range().center());

    customPlot->yAxis2->scaleRange(1.1, customPlot->yAxis2->range().center());

    customPlot->yAxis->setVisible(false);
    customPlot->yAxis->setTickLabels(false);
    customPlot->yAxis2->setVisible(true);
    customPlot->axisRect()->axis(QCPAxis::atRight, 0)->setPadding(30); // add some padding to have space for tags
    //customPlot->axisRect()->axis(QCPAxis::atRight, 1)->setPadding(30); // add some padding to have space for tags


    QList<QCPAxis *> draggableAxes = {customPlot->xAxis,customPlot->yAxis2};
    QList<QCPAxis *> zoomableAxes = {customPlot->xAxis,customPlot->yAxis2};
    customPlot->axisRect()->setRangeDragAxes(draggableAxes);
    customPlot->axisRect()->setRangeZoomAxes(zoomableAxes);


    //линия текущей цены
    // create tags with newly introduced AxisTag class (see axistag.h/.cpp):
    mTag1 = new AxisTag(candlesticks->valueAxis());
    mTag1->setPen(candlesticks->pen());

    infLine = new QCPItemStraightLine(customPlot);


    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    customPlot->setMouseTracking(true);
}

bool PlotDrawer::isMouseOverBar(double x_value)
{
    QDateTime qdt = QDateTime::fromSecsSinceEpoch(x_value);
    qDebug() << "isMouseOverBar     " << qdt;

    for (long long int i = 0; i < candles.size(); ++i)
    {
        if (x_value > candles[i].timeCandleStart && x_value <= candles[i].timeCandleEnd)
        {
            qDebug() << "candle high = " << candles[i].high;
            qDebug() << "candle low = " << candles[i].low;
        }
    }
//    for (auto it = dataContainer.constBegin(); it != dataContainer.constEnd(); ++it)
//    {
//        const QCPFinancialData &dataPoint = *it;
//        if (x_value == dataPoint.key)
//        {
//            qDebug() << "!!!!!!!!!!!!!!!!!!!!!!!!";
//        }
//        else
//        {
//            QDateTime asd = QDateTime::fromSecsSinceEpoch(dataPoint.key);
//            qDebug() << asd;
//        }
//    }
    return true;
}

void PlotDrawer::collectCandleInfo()
{
    candles.clear();
    Candle c;
    long long int currentTime = timeData->first()/binSize;
    c.timeCandleStart = currentTime;
    for (uint i = 0; i < timeData->size(); ++i)
    {
        double currentPrice = priceData->at(i);
        c.high = std::max(c.high, currentPrice);
        c.low = std::min(c.low, currentPrice);
        if ((long long int)timeData->at(i)/binSize == currentTime) [[likely]]
        {
            currentTime = (long long int)(timeData->at(i)/binSize);
        }
        else [[unlikely]]
        {
            c.timeCandleEnd = timeData->at(i);
            c.close = priceData->at(i);
            candles.push_back(c);
            if (i != timeData->size()-1)
            {
                c.timeCandleStart = timeData->at(i+1);
                c.open = priceData->at(i);
                c.high = 0;
                c.close = 0;
            }
        }
    }
}


void PlotDrawer::drawPlot()
{
    if (priceData->isEmpty() || timeData->isEmpty()) return;

    //задаем данные главному графику
    dataContainer = QCPFinancial::timeSeriesToOhlc(*timeData, *priceData, binSize, startTime);
    candlesticks->data()->set(dataContainer);

    //рисуем горизонтальную линию последней цены
    infLine->point1->setCoords(0, priceData->last());
    infLine->point2->setCoords(startTime*100, priceData->last());

    // update the vertical axis tag positions and texts to match the rightmost data point of the graphs:
    customPlot->xAxis->rescale();
    candlesticks->rescaleValueAxis(false, true);
    customPlot->xAxis->setRange(customPlot->xAxis->range().upper, 100, Qt::AlignRight);

    // update the vertical axis tag positions and texts to match the rightmost data point of the graphs:
    mTag1->updatePosition(priceData->last());
    mTag1->setText(QString::number(priceData->last(), 'f', 2));

    if (autoRescale) customPlot->rescaleAxes();
    customPlot->replot();
}

void PlotDrawer::setNewRange(QWheelEvent* e)
{
    if (isXAxisChosen) {
        QCPRange range_x = customPlot->xAxis->range();
        double lower_tmp_x = range_x.lower;
        double upper_tmp_x = range_x.upper;

        if (e->angleDelta().y() < 0) //отдалить
        {
            lower_tmp_x-=1000;
            upper_tmp_x+=1000;
        }
        else //приблизить
        {
            lower_tmp_x+=1000;
            upper_tmp_x-=1000;
        }
        customPlot->xAxis->setRange(lower_tmp_x,upper_tmp_x);
    } else if (isYAxisChosen) {
        QCPRange range_y = customPlot->yAxis2->range();
        double lower_tmp_y = range_y.lower;
        double upper_tmp_y = range_y.upper;

        if (e->angleDelta().y() < 0) //отдалить
        {
            lower_tmp_y*=0.99;
            upper_tmp_y*=1.01;
        }
        else //приблизить
        {
            lower_tmp_y*=1.01;
            upper_tmp_y*=0.99;
        }
        customPlot->yAxis2->setRange(lower_tmp_y,upper_tmp_y);
    } else {
        QCPRange range_x = customPlot->xAxis->range();
        double lower_tmp_x = range_x.lower;
        double upper_tmp_x = range_x.upper;

        if (e->angleDelta().y() < 0) //отдалить
        {
            lower_tmp_x-=1000;
            upper_tmp_x+=1000;
        }
        else //приблизить
        {
            lower_tmp_x+=1000;
            upper_tmp_x-=1000;
        }
        customPlot->xAxis->setRange(lower_tmp_x,upper_tmp_x);
        QCPRange range_y = customPlot->yAxis2->range();
        double lower_tmp_y = range_y.lower;
        double upper_tmp_y = range_y.upper;

        if (e->angleDelta().y() < 0) //отдалить
        {
            lower_tmp_y*=0.99;
            upper_tmp_y*=1.01;
        }
        else //приблизить
        {
            lower_tmp_y*=1.01;
            upper_tmp_y*=0.99;
        }
        customPlot->yAxis2->setRange(lower_tmp_y,upper_tmp_y);
    }

    customPlot->replot();
}

void PlotDrawer::setNewRangeX()
{
    isXAxisChosen = true;
    isYAxisChosen = false;
}

void PlotDrawer::setNewRangeY()
{
    isXAxisChosen = false;
    isYAxisChosen = true;
}

void PlotDrawer::mouseMoved(QMouseEvent *e)
{
    double x_pixel = e->pos().x();
    double x_value = customPlot->xAxis->pixelToCoord(x_pixel);

    QString toolTipText;
    if (isMouseOverBar(x_value))
    {
    }
    // qDebug() << e->position().x();
    // qDebug() << e->position().y();
}

void PlotDrawer::redrawPlotByBinSize_slot(uint bs)
{
    binSize = bs;
    collectCandleInfo();
    candlesticks->setWidth(binSize*0.8); //расстояния между свечками
    dataContainer = QCPFinancial::timeSeriesToOhlc(*timeData, *priceData, binSize, startTime);
    for (auto it = dataContainer.constBegin(); it != dataContainer.constEnd(); ++it)
    {
        const QCPFinancialData &dataPoint = *it;
//        qDebug() << dataPoint.high;
//        qDebug() << dataPoint.low;
//        qDebug() << dataPoint.open;
//        qDebug() << dataPoint.close;
//        QDateTime qdt = QDateTime::fromSecsSinceEpoch(dataPoint.key);
//        qDebug() << qdt;
//        qDebug() << "=======================";
    }

    candlesticks->data()->set(dataContainer);
    customPlot->replot();
//    drawPlot();
}
