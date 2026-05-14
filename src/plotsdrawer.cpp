#include "plotsdrawer.h"
#include "ui_plotsdrawer.h"

PlotsDrawer::PlotsDrawer(QWidget *parent)
    : QWidget(parent)
    , binSize(60) //интервал в секундах
    , autoRescale(true)
    , m_syncing(false)
    , ui(new Ui::PlotsDrawer)
{
    ui->setupUi(this);

    start = QDateTime(QDate(2026, 1, 1), QTime(9,59,50));
    start.setTimeSpec(Qt::UTC);
    startTime = start.currentSecsSinceEpoch();

    volPlot = new VolumePlot(ui->PlotsWidget);
    volPlot->initPlot(binSize, startTime);

    finPlot = new FinancialPlot(ui->PlotsWidget);
    finPlot->initPlot(binSize, startTime);
    finPlot->customPlotFinancial->installEventFilter(this);

    // Синхронизация ТОЛЬКО оси X при изменении candle plot
    connect(finPlot->customPlotFinancial->xAxis,
            QOverload<const QCPRange &>::of(&QCPAxis::rangeChanged),
            this, &PlotsDrawer::onCandleXAxisChanged);
}

void PlotsDrawer::onCandleXAxisChanged(const QCPRange &range)
{
    if (m_syncing) return;


    m_syncing = true;
    // Обновляем только X ось volume plot
    volPlot->customPlotVolume->xAxis->setRange(range);
    volPlot->customPlotVolume->replot();
    m_syncing = false;
}

PlotsDrawer::~PlotsDrawer()
{
    delete ui;
}


void PlotsDrawer::drawPlot()
{
    if (priceData->isEmpty() || timeData->isEmpty()) return;

    finPlot->customPlotFinancial->rescaleAxes(true);
    volPlot->customPlotVolume->rescaleAxes(true);

    finPlot->customPlotFinancial->replot();

    //делаем так, чтоб график объемов занимал 20%
    QCPRange autoRange = volPlot->customPlotVolume->yAxis2->range();
    volPlot->customPlotVolume->yAxis2->setRange(autoRange.lower, autoRange.upper * 5);
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

bool PlotsDrawer::eventFilter(QObject *obj, QEvent *event)
{
    // Перехватываем события колеса мыши
    if (event->type() == QEvent::Wheel)
    {
        QWheelEvent *wheelEvent = static_cast<QWheelEvent*>(event);

        // Проверяем, что событие от свечного графика
        if (obj == finPlot->customPlotFinancial)
        {
            // Получаем текущий диапазон X
            QCPRange xRange = finPlot->customPlotFinancial->xAxis->range();
            double center = xRange.center();
            double range = xRange.size();

            // Коэффициент масштабирования
            double scaleFactor = 1.15;

            // Определяем направление прокрутки
            if (wheelEvent->angleDelta().y() < 0)
            {
                // Прокрутка вверх - уменьшаем масштаб (показываем больше)
                range *= scaleFactor;
            }
            else
            {
                // Прокрутка вниз - увеличиваем масштаб (показываем меньше)
                range /= scaleFactor;
            }

            // Устанавливаем новый диапазон X
            QCPRange newRange(center - range / 2.0, center + range / 2.0);

            m_syncing = true;
            finPlot->customPlotFinancial->xAxis->setRange(newRange);
            volPlot->customPlotVolume->xAxis->setRange(newRange);
            finPlot->customPlotFinancial->replot();
            volPlot->customPlotVolume->replot();
            m_syncing = false;

            return true;  // Событие обработано
        }
    }
    return false;
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

    drawPlot();
}

