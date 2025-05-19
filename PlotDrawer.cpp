#include "PlotDrawer.h"

PlotDrawer::PlotDrawer(QCustomPlot* cp)
    : binSize(60) //интервал в секундах
    , autoRescale(true)
    , isXAxisChosen(false)
    , isYAxisChosen(false)
{
    this->customPlot = cp;

    start = QDateTime(QDate(2025, 5, 3), QTime(9,59,50));

    start.setTimeSpec(Qt::UTC);
    startTime = start.currentSecsSinceEpoch();

    candlesticks = new QCPFinancial(customPlot->xAxis, customPlot->yAxis2);

    candlesticks->setChartStyle(QCPFinancial::csCandlestick);
    candlesticks->setWidth(binSize*0.9); //расстояния между свечками
    candlesticks->setTwoColored(true);
    candlesticks->setBrushPositive(QColor(0, 215, 0));
    candlesticks->setBrushNegative(QColor(240, 0, 0));
    candlesticks->setPenPositive(QPen(QColor(0, 0, 0)));
    candlesticks->setPenNegative(QPen(QColor(0, 0, 0)));

    QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
    dateTimeTicker->setDateTimeSpec(Qt::UTC);
    dateTimeTicker->setDateTimeFormat("dd. MM. yyyy\n hh:mm:ss");
    customPlot->xAxis->setTicker(dateTimeTicker);
    customPlot->xAxis->setRange(QCPRange(startTime, startTime+60));
    customPlot->xAxis->scaleRange(1.025, customPlot->xAxis->range().center());

    customPlot->yAxis2->scaleRange(1.1, customPlot->yAxis2->range().center());

    customPlot->setInteractions(QCP::iRangeDrag | QCP::iSelectAxes);

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

}


void PlotDrawer::drawPlot()
{
    if (priceData->isEmpty() || timeData->isEmpty()) return;

    //задаем данные главному графику
    candlesticks->data()->set(QCPFinancial::timeSeriesToOhlc(*timeData, *priceData, binSize, startTime));

    //рисуем горизонтальную линию последней цены
    infLine->point1->setCoords(0, priceData->last());
    infLine->point2->setCoords(startTime*100, priceData->last());

    // update the vertical axis tag positions and texts to match the rightmost data point of the graphs:
    //customPlot->xAxis->rescale();
    //candlesticks->rescaleValueAxis(false, true);
    //customPlot->xAxis->setRange(customPlot->xAxis->range().upper, 100, Qt::AlignRight);

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
            lower_tmp_x-=100;
            upper_tmp_x+=100;
        }
        else //приблизить
        {
            lower_tmp_x+=100;
            upper_tmp_x-=100;
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
            lower_tmp_x-=100;
            upper_tmp_x+=100;
        }
        else //приблизить
        {
            lower_tmp_x+=100;
            upper_tmp_x-=100;
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
    e->ignore();
    // qDebug() << e->position().x();
    // qDebug() << e->position().y();
}
