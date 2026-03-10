#include "PlotDrawer.h"

PlotDrawer::PlotDrawer(QCustomPlot* cp)
    : binSize(60) //интервал в секундах
    , autoRescale(true)
{

    this->customPlot = cp;

    start = QDateTime(QDate(2026, 1, 1), QTime(9,59,50));

    start.setTimeSpec(Qt::UTC);
    startTime = start.currentSecsSinceEpoch();

    initMainChart();
    initVolChart();

    customPlot->yAxis->setVisible(true);
    customPlot->yAxis2->setVisible(true);
    customPlot->xAxis->grid()->setVisible(true);
    customPlot->yAxis->grid()->setVisible(true);

    //линия текущей цены
    // create tags with newly introduced AxisTag class (see axistag.h/.cpp):
    mTag1 = new AxisTag(candlesticks->valueAxis());
    mTag1->setPen(candlesticks->pen());

    infLine = new QCPItemStraightLine(customPlot);

    customPlot->setInteractions(/*QCP::iRangeDrag |*/ QCP::iRangeZoom);
    customPlot->setMouseTracking(true);

    mDraggingCustomItem = false;
}

void PlotDrawer::isMouseOverBar(double x_value)
{
    //qDebug() << "candles.size() = " << candles.size();
    for (uint i = 0; i < candles.size(); ++i)
    {
        if (x_value > candles[i].timeCandleStart && x_value <= candles[i].timeCandleEnd)
        {
            // qDebug() << "candle high = " << candles[i].high;
            // qDebug() << "candle low = " << candles[i].low;
        }
    }
}

void PlotDrawer::collectCandleInfo()
{
    candles.clear();
    Candle c;
    double previousTime = timeData->first();
    c.timeCandleStart = previousTime;
    c.open = priceData->first();
    for (uint i = 0; i < timeData->size(); ++i)
    {
        double currentPrice = priceData->at(i);
        c.high = std::max(c.high, currentPrice);
        c.low = std::min(c.low, currentPrice);
        c.volume += quantityData->at(i);
        if (timeData->at(i) - previousTime > binSize || timeData->at(i) - previousTime == binSize)
        {
            c.timeCandleEnd = timeData->at(i);
            c.close = currentPrice;
            candles.push_back(c);
            //at least one more candle
            if (i != timeData->size()-1)
            {
                previousTime = timeData->at(i+1);
                c.timeCandleStart = previousTime;
                c.open = currentPrice;
                c.high = 0;
                c.low = 999999999;
                c.close = 0;
                c.volume = 0;
            }
        }
    }

    open.clear();
    high.clear();
    low.clear();
    close.clear();
    time.clear();

    open.resize(candles.size());
    high.resize(candles.size());
    low.resize(candles.size());
    close.resize(candles.size());
    time.resize(candles.size());

    //for volume
    volumePositive.clear();
    timePositive.clear();
    volumeNegative.clear();
    timeNegative.clear();

    volumePositive.resize(candles.size());
    timePositive.resize(candles.size());
    volumeNegative.resize(candles.size());
    timeNegative.resize(candles.size());


    for (int i = 0; i < candles.size(); ++i)
    {
        open[i] = candles[i].open;
        high[i] = candles[i].high;
        low[i] = candles[i].low;
        close[i] = candles[i].close;
        time[i] = candles[i].timeCandleStart;

        //for volume
        if (candles[i].open > candles[i].close)
        {
            timeNegative[i] = candles[i].timeCandleStart;
            volumeNegative[i] = candles[i].volume;

            timePositive[i] = candles[i].timeCandleStart;
            volumePositive[i] = 0;
        }
        else
        {
            timeNegative[i] = candles[i].timeCandleStart;
            volumeNegative[i] = 0;

            timePositive[i] = candles[i].timeCandleStart;
            volumePositive[i] = candles[i].volume;
        }
    }
}

void PlotDrawer::mousePressEvent(QMouseEvent *event)
{
    QPoint globalPos = QCursor::pos();
    qDebug() << globalPos;
    QWidget *clickedItem = QApplication::widgetAt(globalPos);

    //
    if (clickedItem == customPlot)
     {
         qDebug() << "QWEQWEQWEQWE";
        mDraggingCustomItem = true;
        mDragStartPos = event->pos();
        // ... initialize your drag state
    }
}

void PlotDrawer::initMainChart()
{
    candlesticks = new QCPFinancial(customPlot->xAxis, customPlot->yAxis2);

    candlesticks->setName("Candles");
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
    // customPlot->yAxis->scaleRange(1.1, customPlot->yAxis2->range().center());
    customPlot->yAxis2->scaleRange(1.1, customPlot->yAxis2->range().center());


    customPlot->axisRect()->axis(QCPAxis::atRight, 0)->setPadding(30); // add some padding to have space for tags
    //customPlot->axisRect()->axis(QCPAxis::atRight, 1)->setPadding(30); // add some padding to have space for tags

    QList<QCPAxis *> draggableAxes = {customPlot->xAxis,customPlot->yAxis2};
    QList<QCPAxis *> zoomableAxes = {customPlot->xAxis,customPlot->yAxis2};
    customPlot->axisRect()->setRangeDragAxes(draggableAxes);
    customPlot->axisRect()->setRangeZoomAxes(zoomableAxes);
}

void PlotDrawer::initVolChart()
{
    //pos
    volumeBarsPositive = new QCPBars(customPlot->xAxis, customPlot->yAxis);
    volumeBarsPositive->setBrush(QColor(100, 180, 110, 255));
    volumeBarsPositive->setWidth(0.8*binSize);//??
    volumeBarsPositive->setPen(Qt::NoPen);

    //neg
    volumeBarsNegative = new QCPBars(customPlot->xAxis, customPlot->yAxis);
    volumeBarsNegative->setWidth(0.8*binSize);//??
    volumeBarsNegative->setBrush(QColor(180, 90, 90, 255));
    volumeBarsNegative->setPen(Qt::NoPen);

    // // create bottom axis rect for volume bar chart:
    // QCPAxisRect *volumeAxisRect = new QCPAxisRect(customPlot);

    // customPlot->plotLayout()->addElement(1, 0, volumeAxisRect);
    // volumeAxisRect->setMaximumSize(QSize(QWIDGETSIZE_MAX, 100));
    // volumeAxisRect->axis(QCPAxis::atBottom)->setLayer("axes");
    // volumeAxisRect->axis(QCPAxis::atBottom)->grid()->setLayer("grid");


    // // bring bottom and main axis rect closer together:
    // customPlot->plotLayout()->setRowSpacing(0);
    // volumeAxisRect->setAutoMargins(QCP::msLeft|QCP::msRight|QCP::msBottom);
    // volumeAxisRect->setMargins(QMargins(0, 0, 0, 0));

    // // create two bar plottables, for positive (green) and negative (red) volume bars:
    // customPlot->setAutoAddPlottableToLegend(false);
    // volumePos = new QCPBars(volumeAxisRect->axis(QCPAxis::atBottom), volumeAxisRect->axis(QCPAxis::atRight));
    // volumeNeg = new QCPBars(volumeAxisRect->axis(QCPAxis::atBottom), volumeAxisRect->axis(QCPAxis::atRight));

    // volumePos->setPen(Qt::NoPen);
    // volumePos->setBrush(QColor(100, 180, 110));
    // volumeNeg->setPen(Qt::NoPen);
    // volumeNeg->setBrush(QColor(180, 90, 90));

    // //volumeAxisRect->axis(QCPAxis::atBottom)->setTicker(dateTimeTicker);
    // volumeAxisRect->axis(QCPAxis::atLeft)->setVisible(false);
    // volumeAxisRect->axis(QCPAxis::atRight)->setVisible(true);
}


void PlotDrawer::drawPlot()
{
    if (priceData->isEmpty() || timeData->isEmpty()) return;

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

    if (autoRescale)
        customPlot->rescaleAxes();

    customPlot->replot();
}

void PlotDrawer::setNewRange(QWheelEvent* e)
{
    QCPRange range_y_good = customPlot->yAxis->range();

    QCPRange range_y = customPlot->yAxis2->range();
    double upper_tmp_y = range_y.upper;
    double lower_tmp_y = range_y.lower;
    if (e->angleDelta().y() < 0) //отдалить
    {
        customPlot->yAxis2->setRange(lower_tmp_y*0.99,upper_tmp_y*1.01);
    }
    customPlot->yAxis->setRange(range_y_good);
    // if (isXAxisChosen) {
    //     QCPRange range_x = customPlot->xAxis->range();
    //     double lower_tmp_x = range_x.lower;
    //     double upper_tmp_x = range_x.upper;

    //     if (e->angleDelta().y() < 0) //отдалить
    //     {
    //         lower_tmp_x-=1000;
    //         upper_tmp_x+=1000;
    //     }
    //     else //приблизить
    //     {
    //         lower_tmp_x+=1000;
    //         upper_tmp_x-=1000;
    //     }
    //     customPlot->xAxis->setRange(lower_tmp_x,upper_tmp_x);
    // } else if (isYAxisChosen) {
    //     QCPRange range_y = customPlot->yAxis2->range();
    //     double lower_tmp_y = range_y.lower;
    //     double upper_tmp_y = range_y.upper;

    //     if (e->angleDelta().y() < 0) //отдалить
    //     {
    //         lower_tmp_y*=0.99;
    //         upper_tmp_y*=1.01;
    //     }
    //     else //приблизить
    //     {
    //         lower_tmp_y*=1.01;
    //         upper_tmp_y*=0.99;
    //     }
    //     customPlot->yAxis2->setRange(lower_tmp_y,upper_tmp_y);
    // } else {
    //     QCPRange range_x = customPlot->xAxis->range();
    //     double lower_tmp_x = range_x.lower;
    //     double upper_tmp_x = range_x.upper;

    //     if (e->angleDelta().y() < 0) //отдалить
    //     {
    //         lower_tmp_x-=1000;
    //         upper_tmp_x+=1000;
    //     }
    //     else //приблизить
    //     {
    //         lower_tmp_x+=1000;
    //         upper_tmp_x-=1000;
    //     }
    //     customPlot->xAxis->setRange(lower_tmp_x,upper_tmp_x);
    //     QCPRange range_y = customPlot->yAxis2->range();
    //     double lower_tmp_y = range_y.lower;
    //     double upper_tmp_y = range_y.upper;

    //     if (e->angleDelta().y() < 0) //отдалить
    //     {
    //         lower_tmp_y*=0.99;
    //         upper_tmp_y*=1.01;
    //     }
    //     else //приблизить
    //     {
    //         lower_tmp_y*=1.01;
    //         upper_tmp_y*=0.99;
    //     }
    //     customPlot->yAxis2->setRange(lower_tmp_y,upper_tmp_y);
    // }

    customPlot->replot();
}

void PlotDrawer::mouseMoved(QMouseEvent *e)
{
    double x_pixel = e->pos().x();
    double x_value = customPlot->xAxis->pixelToCoord(x_pixel);

    QString toolTipText;
    isMouseOverBar(x_value);
    {
    }
    // qDebug() << e->position().x();
    // qDebug() << e->position().y();

    //drag and drop
    if (mDraggingCustomItem)
    {
        QCPRange niceRange = customPlot->yAxis->range();

        double upper_y = customPlot->yAxis2->range().upper;
        double lower_y = customPlot->yAxis2->range().lower;

        double upper_x = customPlot->xAxis->range().upper;
        double lower_x = customPlot->xAxis->range().lower;

        double current_x = e->pos().x();
        double current_y = e->pos().y();

        double step_x = mDragStartPos.x() - current_x;
        double step_y = mDragStartPos.y() - current_y;

        customPlot->xAxis->setRange(lower_x - step_x, upper_x - step_x);
        customPlot->yAxis2->setRange(lower_y - step_y, upper_y - step_y);

        mDragStartPos = e->pos();

        customPlot->yAxis->setRange(niceRange);
        customPlot->replot();
    }
}

void PlotDrawer::mousePressed(QMouseEvent *e)
{
    mDraggingCustomItem = true;
    mDragStartPos = e->pos();
}

void PlotDrawer::mouseReleased(QMouseEvent *e)
{
    mDraggingCustomItem = false;
}

void PlotDrawer::redrawPlotByBinSizeChange_slot(uint bs)
{
    binSize = bs;
    candlesticks->data().clear();
    collectCandleInfo();
    //задаем данные графику объемов
    // volumePos->data().clear();
    // volumeNeg->data().clear();
    // for (int i=0; i<candles.size(); ++i)
    // {
    //     long long v = candles[i].volume;
    //     if (candles[i].open > candles[i].close)
    //     {
    //         volumeNeg->addData(candles[i].timeCandleStart, qAbs(v));
    //     }
    //     else
    //     {
    //         volumePos->addData(candles[i].timeCandleStart, qAbs(v));
    //     }
    // }

    // volumeNeg->setWidth(binSize);
    // volumePos->setWidth(binSize);

    candlesticks->setWidth(binSize*0.8); //расстояния между свечками

    candlesticks->setData(time,
                          open,
                          high,
                          low,
                          close);

    volumeBarsPositive->setData(timePositive,
                                volumePositive);
    volumeBarsPositive->setWidth(binSize*0.8);

    volumeBarsNegative->setData(timeNegative,
                                volumeNegative);
    volumeBarsNegative->setWidth(binSize*0.8);

    customPlot->rescaleAxes(true);
    customPlot->replot();
//    drawPlot();
}
