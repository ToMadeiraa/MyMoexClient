#include "plotsdrawer.h"
#include "ui_plotsdrawer.h"

PlotsDrawer::PlotsDrawer(QWidget *parent)
    : QWidget(parent)
    , binSize(60) //интервал в секундах
    , autoRescale(true)
    , ui(new Ui::PlotsDrawer)
{
    ui->setupUi(this);

    start = QDateTime(QDate(2026, 1, 1), QTime(9,59,50));
    start.setTimeSpec(Qt::UTC);
    startTime = start.currentSecsSinceEpoch();

    finPlot = ui->PlotWidgetCandlesticks;
    volPlot = ui->PlotWidgetVolume;

    finPlot->initPlot(binSize, startTime);
    volPlot->initPlot(binSize, startTime);
}

PlotsDrawer::~PlotsDrawer()
{
    delete ui;
}


void PlotsDrawer::drawPlot()
{
    if (priceData->isEmpty() || timeData->isEmpty()) return;

    //рисуем горизонтальную линию последней цены
    finPlot->infLine->point1->setCoords(0, priceData->last());
    finPlot->infLine->point2->setCoords(startTime*100, priceData->last());

    // update the vertical axis tag positions and texts to match the rightmost data point of the graphs:
    finPlot->customPlotFinancial->xAxis->rescale();
    finPlot->candlesticks->rescaleValueAxis(false, true);
    finPlot->customPlotFinancial->xAxis->setRange(finPlot->customPlotFinancial->xAxis->range().upper, 100, Qt::AlignRight);

    // update the vertical axis tag positions and texts to match the rightmost data point of the graphs:
    finPlot->mTag1->updatePosition(priceData->last());
    finPlot->mTag1->setText(QString::number(priceData->last(), 'f', 2));

    if (autoRescale)
        finPlot->customPlotFinancial->rescaleAxes();

    finPlot->customPlotFinancial->replot();
    volPlot->customPlotVolume->replot();
}

void PlotsDrawer::clearSecurityData()
{
    timeData->clear();
    priceData->clear();
    quantityData->clear();
    buysellData->clear();
    finPlot->candlesticks->data().clear();
}


void PlotsDrawer::collectCandleInfo()
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

    finPlot->open.clear();
    finPlot->high.clear();
    finPlot->low.clear();
    finPlot->close.clear();
    finPlot->time.clear();

    finPlot->open.resize(candles.size());
    finPlot->high.resize(candles.size());
    finPlot->low.resize(candles.size());
    finPlot->close.resize(candles.size());
    finPlot->time.resize(candles.size());

    //for volume
    volPlot->volumePositive.clear();
    volPlot->timePositive.clear();
    volPlot->volumeNegative.clear();
    volPlot->timeNegative.clear();

    volPlot->volumePositive.resize(candles.size());
    volPlot->timePositive.resize(candles.size());
    volPlot->volumeNegative.resize(candles.size());
    volPlot->timeNegative.resize(candles.size());


    for (int i = 0; i < candles.size(); ++i)
    {
        finPlot->open[i] = candles[i].open;
        finPlot->high[i] = candles[i].high;
        finPlot->low[i] = candles[i].low;
        finPlot->close[i] = candles[i].close;
        finPlot->time[i] = candles[i].timeCandleStart;

        //for volume
        if (candles[i].open > candles[i].close)
        {
            volPlot->timeNegative[i] = candles[i].timeCandleStart;
            volPlot->volumeNegative[i] = candles[i].volume;

            volPlot->timePositive[i] = candles[i].timeCandleStart;
            volPlot->volumePositive[i] = 0;
        }
        else
        {
            volPlot->timeNegative[i] = candles[i].timeCandleStart;
            volPlot->volumeNegative[i] = 0;

            volPlot->timePositive[i] = candles[i].timeCandleStart;
            volPlot->volumePositive[i] = candles[i].volume;
        }
    }
}


void PlotsDrawer::isMouseOverBar(double x_value)
{
    // //qDebug() << "candles.size() = " << candles.size();
    // for (uint i = 0; i < candles.size(); ++i)
    // {
    //     if (x_value > candles[i].timeCandleStart && x_value <= candles[i].timeCandleEnd)
    //     {
    //         // qDebug() << "candle high = " << candles[i].high;
    //         // qDebug() << "candle low = " << candles[i].low;
    //     }
    // }
}


void PlotsDrawer::mouseMoved(QMouseEvent *e)
{

}

void PlotsDrawer::mousePressed(QMouseEvent *e)
{

}

void PlotsDrawer::mouseReleased(QMouseEvent *e)
{

}

void PlotsDrawer::redrawPlotByBinSizeChange_slot(uint bs)
{
    binSize = bs;
    finPlot->candlesticks->data().clear();
    collectCandleInfo();
    finPlot->candlesticks->setWidth(binSize*0.8); //расстояния между свечками
    finPlot->setCandlesData();
    volPlot->setCandlesData();
    volPlot->volumeBarsPositive->setWidth(binSize*0.8);
    volPlot->volumeBarsNegative->setWidth(binSize*0.8);

    finPlot->customPlotFinancial->rescaleAxes(true);
    volPlot->customPlotVolume->rescaleAxes(true);
    finPlot->customPlotFinancial->replot();
    volPlot->customPlotVolume->replot();

    volPlot->volumeBarsNegative->data().clear();
    volPlot->volumeBarsPositive->data().clear();
    for (int i=0; i<candles.size(); ++i)
    {
        long long v = candles[i].volume;
        if (candles[i].open > candles[i].close)
        {
            volPlot->volumeBarsNegative->addData(candles[i].timeCandleStart, qAbs(v));
        }
        else
        {
            volPlot->volumeBarsPositive->addData(candles[i].timeCandleStart, qAbs(v));
        }
    }

    volPlot->volumeBarsNegative->setWidth(binSize);
    volPlot->volumeBarsPositive->setWidth(binSize);
}

