#include "plotsdrawer.h"
#include "ui_plotsdrawer.h"

PlotsDrawer::PlotsDrawer(QWidget *parent)
    : QWidget(parent)
    , binSize(60) //интервал в секундах
    , m_syncing(false)
    , ui(new Ui::PlotsDrawer)
{
    ui->setupUi(this);

    start = QDateTime(QDate(2026, 1, 1), QTime(9,59,50));
    start.setTimeSpec(Qt::UTC);
    startTime = start.currentSecsSinceEpoch();

    volWidget = new VolumeWidget(ui->PlotsWidget);
    volWidget->initPlot(binSize, startTime);
    hideAllAxes(volWidget->volumePlot);

    finWidget = new FinancialWidget(ui->PlotsWidget);
    finWidget->initPlot(binSize, startTime);
    finWidget->financialPlot->installEventFilter(this);
    hideAllAxes(finWidget->financialPlot);

    ui->PlotsWidget->setFixedSize(WINDOW_WIDTH - Y_AXIS_WIDTH, WINDOW_HEIGHT - X_AXIS_HEIGHT);
    ui->y2AxisWidget->setFixedSize(Y_AXIS_WIDTH, WINDOW_HEIGHT - X_AXIS_HEIGHT);
    ui->xAxisWidget->setFixedSize(WINDOW_WIDTH - Y_AXIS_WIDTH, X_AXIS_HEIGHT);

    volWidget->volumePlot->setFixedSize(800-70, 600-40);
    volWidget->volumePlot->setGeometry(0, 0, 800-70, 600-40);
    volWidget->volumePlot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    finWidget->financialPlot->setFixedSize(800-70, 600-40);
    finWidget->financialPlot->setGeometry(0, 0, 800-70, 600-40);
    finWidget->financialPlot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    setupAxisPlots();
    createPlotConnections();
}

PlotsDrawer::~PlotsDrawer()
{
    delete ui;
}

void PlotsDrawer::drawPlot()
{
    if (priceData->isEmpty() || timeData->isEmpty()) return;

    finWidget->financialPlot->rescaleAxes(true);
    volWidget->volumePlot->rescaleAxes(true);

    finWidget->financialPlot->replot();

    //делаем так, чтоб график объемов занимал 20%
    QCPRange autoRange = volWidget->volumePlot->yAxis2->range();
    volWidget->volumePlot->yAxis2->setRange(autoRange.lower, autoRange.upper * 5);
    volWidget->volumePlot->replot();
}

void PlotsDrawer::onCandleXAxisChanged(const QCPRange &range)
{
    if (m_syncing) return;

    m_syncing = true;
    // Обновляем только X ось volume plot
    volWidget->volumePlot->xAxis->setRange(range);
    volWidget->volumePlot->replot();
    m_syncing = false;
}

void PlotsDrawer::onCandleYAxisChanged(const QCPRange &range)
{
    Q_UNUSED(range);
    // Обработка при необходимости
}

void PlotsDrawer::onXAxisPlotRangeChanged(const QCPRange &range)
{
    if (m_syncing) return;

    m_syncing = true;

    // Синхронизируем все графики с новым диапазоном X
    finWidget->financialPlot->xAxis->setRange(range);
    volWidget->volumePlot->xAxis->setRange(range);

    finWidget->financialPlot->replot();
    volWidget->volumePlot->replot();

    m_syncing = false;
}

void PlotsDrawer::syncAxesToCandleX(const QCPRange &range)
{
    if (m_syncing) return;

    m_syncing = true;

    // Синхронизируем ось X на отдельном plot'е
    m_xAxisPlot->xAxis->setRange(range);
    m_xAxisPlot->replot();

    m_syncing = false;
}

void PlotsDrawer::syncAxesToCandleY(const QCPRange &range)
{
    if (m_syncing) return;

    m_syncing = true;

    // Синхронизируем ось Y на отдельном plot'е
    m_yAxisPlot->yAxis2->setRange(range);
    m_yAxisPlot->replot();

    m_syncing = false;
}


void PlotsDrawer::clearSecurityData()
{
    timeData->clear();
    priceData->clear();
    quantityData->clear();
    buysellData->clear();
    finWidget->candlesticks->data().clear();
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

    finWidget->open.clear();
    finWidget->high.clear();
    finWidget->low.clear();
    finWidget->close.clear();
    finWidget->time.clear();

    finWidget->open.resize(candles.size());
    finWidget->high.resize(candles.size());
    finWidget->low.resize(candles.size());
    finWidget->close.resize(candles.size());
    finWidget->time.resize(candles.size());

    //for volume
    volWidget->volumePositive.clear();
    volWidget->timePositive.clear();
    volWidget->volumeNegative.clear();
    volWidget->timeNegative.clear();

    volWidget->volumePositive.resize(candles.size());
    volWidget->timePositive.resize(candles.size());
    volWidget->volumeNegative.resize(candles.size());
    volWidget->timeNegative.resize(candles.size());


    for (int i = 0; i < candles.size(); ++i)
    {
        finWidget->open[i] = candles[i].open;
        finWidget->high[i] = candles[i].high;
        finWidget->low[i] = candles[i].low;
        finWidget->close[i] = candles[i].close;
        finWidget->time[i] = candles[i].timeCandleStart;

        //for volume
        if (candles[i].open > candles[i].close)
        {
            volWidget->timeNegative[i] = candles[i].timeCandleStart;
            volWidget->volumeNegative[i] = candles[i].volume;

            volWidget->timePositive[i] = candles[i].timeCandleStart;
            volWidget->volumePositive[i] = 0;
        }
        else
        {
            volWidget->timeNegative[i] = candles[i].timeCandleStart;
            volWidget->volumeNegative[i] = 0;

            volWidget->timePositive[i] = candles[i].timeCandleStart;
            volWidget->volumePositive[i] = candles[i].volume;
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
        if (obj == finWidget->financialPlot)
        {
            // Получаем текущий диапазон X
            QCPRange xRange = finWidget->financialPlot->xAxis->range();
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
            finWidget->financialPlot->xAxis->setRange(newRange);
            volWidget->volumePlot->xAxis->setRange(newRange);
            m_xAxisPlot->xAxis->setRange(newRange);
            finWidget->financialPlot->replot();
            volWidget->volumePlot->replot();
            m_xAxisPlot->replot();
            m_syncing = false;

            return true;  // Событие обработано
        }


        // Обработка колеса мыши на xAxisPlot
        if (obj == m_xAxisPlot)
        {
            // Получаем текущий диапазон X с оси X plot
            QCPRange xRange = m_xAxisPlot->xAxis->range();
            double center = xRange.center();
            double range = xRange.size();

            double scaleFactor = 1.15;

            if (wheelEvent->angleDelta().y() > 0)
            {
                range *= scaleFactor;  // Zoom out
            }
            else
            {
                range /= scaleFactor;  // Zoom in
            }

            QCPRange newRange(center - range / 2.0, center + range / 2.0);

            m_syncing = true;

            // Обновляем все связанные графики
            m_xAxisPlot->xAxis->setRange(newRange);
            finWidget->financialPlot->xAxis->setRange(newRange);
            volWidget->volumePlot->xAxis->setRange(newRange);

            m_xAxisPlot->replot();
            finWidget->financialPlot->replot();
            volWidget->volumePlot->replot();

            m_syncing = false;

            return true;
        }
    }



     return false;
}


void PlotsDrawer::hideAllAxes(QCustomPlot *plot)
{
    if (!plot) return;

    QCPAxisRect *axisRect = plot->axisRect();

    QList<QCPAxis::AxisType> axisTypes = {
        QCPAxis::atLeft, QCPAxis::atRight,
        QCPAxis::atTop, QCPAxis::atBottom
    };

    for (QCPAxis::AxisType type : axisTypes)
    {
        QCPAxis *axis = axisRect->axis(type);
        axis->setVisible(false);
        axis->setTicks(false);
        axis->setTickLabels(false);
        axis->grid()->setVisible(false);
        axis->grid()->setPen(QPen(Qt::transparent));
        axis->setSubTicks(false);
        axis->setTickPen(QPen(Qt::transparent));
        axis->setSubTickPen(QPen(Qt::transparent));
        axis->setBasePen(QPen(Qt::transparent));
        axis->setLabel("");
    }

    axisRect->setAutoMargins(QCP::msNone);
    axisRect->setMargins(QMargins(0, 0, 0, 0));

    plot->replot();
}

void PlotsDrawer::createPlotConnections()
{
    // Синхронизация оси X графиков candleplot и volumeplot
    connect(finWidget->financialPlot->xAxis,
            QOverload<const QCPRange &>::of(&QCPAxis::rangeChanged),
            this, &PlotsDrawer::onCandleXAxisChanged);

    // Синхронизация оси X основного графика с осевым plot'ом
    connect(finWidget->financialPlot->xAxis,
            QOverload<const QCPRange &>::of(&QCPAxis::rangeChanged),
            this, &PlotsDrawer::syncAxesToCandleX);

    // Синхронизация оси Y основного графика с осевым plot'ом
    connect(finWidget->financialPlot->yAxis,
            QOverload<const QCPRange &>::of(&QCPAxis::rangeChanged),
            this, &PlotsDrawer::syncAxesToCandleY);
}

void PlotsDrawer::setupAxisPlots()
{
    // === X AXIS PLOT (снизу) ===
    m_xAxisPlot = new QCustomPlot(ui->xAxisWidget);
    m_xAxisPlot->setAttribute(Qt::WA_TranslucentBackground);
    // m_xAxisPlot->setGeometry(0, WINDOW_HEIGHT - X_AXIS_HEIGHT,
    //                          WINDOW_WIDTH - Y_AXIS_WIDTH, X_AXIS_HEIGHT);
    m_xAxisPlot->setFixedSize(WINDOW_WIDTH, X_AXIS_HEIGHT);

    m_xAxisPlot->setBackground(QBrush(QColor(0, 0, 0, 80)));  // Полупрозрачный фон
    m_xAxisPlot->setOpenGl(false);

    // Настройка оси X
    m_xAxis = m_xAxisPlot->xAxis;
    m_xAxis->setVisible(true);
    m_xAxis->setTicks(true);
    m_xAxis->setTickLabels(true);
    m_xAxis->setSubTicks(true);

    // Внешний вид оси X
    m_xAxis->setBasePen(QPen(QColor(200, 200, 200, 220), 2));
    m_xAxis->setTickPen(QPen(QColor(200, 200, 200, 200), 1));
    m_xAxis->setSubTickPen(QPen(QColor(200, 200, 200, 150), 1));
    m_xAxis->setTickLabelColor(QColor(220, 220, 220, 230));

    QFont xFont;
    xFont.setPointSize(8);
    m_xAxis->setTickLabelFont(xFont);

    // Скрываем все остальные оси
    m_xAxisPlot->yAxis->setVisible(false);
    m_xAxisPlot->xAxis2->setVisible(false);
    m_xAxisPlot->yAxis2->setVisible(false);

    // Настройка отступов
    m_xAxisPlot->axisRect()->setAutoMargins(QCP::msBottom);
    m_xAxisPlot->axisRect()->setMargins(QMargins(0, 0, 0, 0));

    m_xAxisPlot->setInteractions(QCP::iNone);  // Отключаем взаимодействие

    QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
    dateTimeTicker->setDateTimeSpec(Qt::UTC);
    dateTimeTicker->setDateTimeFormat("dd. MM. yyyy\n hh:mm:ss");
    m_xAxisPlot->xAxis->setTicker(dateTimeTicker);

    // Включаем взаимодействие для оси X (только горизонтальное)
    m_xAxisPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    m_xAxisPlot->axisRect()->setRangeDrag(Qt::Horizontal);
    m_xAxisPlot->axisRect()->setRangeZoom(Qt::Horizontal);

    // Добавляем обработку колеса мыши для оси X
    connect(m_xAxisPlot->xAxis,
            QOverload<const QCPRange &>::of(&QCPAxis::rangeChanged),
            this, &PlotsDrawer::onXAxisPlotRangeChanged);

    // === Y AXIS PLOT (справа) ===
    m_yAxisPlot = new QCustomPlot(ui->y2AxisWidget);
    m_yAxisPlot->setAttribute(Qt::WA_TranslucentBackground);
    m_yAxisPlot->setFixedSize(Y_AXIS_WIDTH, WINDOW_HEIGHT);

    m_yAxisPlot->setBackground(QBrush(QColor(0, 0, 0, 80)));  // Полупрозрачный фон
    m_yAxisPlot->setOpenGl(false);

    // Настройка оси Y (справа)
    m_yAxis = m_yAxisPlot->yAxis2;
    m_yAxis->setVisible(true);
    m_yAxis->setTicks(true);
    m_yAxis->setTickLabels(true);
    m_yAxis->setSubTicks(true);

    // Внешний вид оси Y
    m_yAxis->setBasePen(QPen(QColor(200, 200, 200, 220), 2));
    m_yAxis->setTickPen(QPen(QColor(200, 200, 200, 200), 1));
    m_yAxis->setSubTickPen(QPen(QColor(200, 200, 200, 150), 1));
    m_yAxis->setTickLabelColor(QColor(220, 220, 220, 230));

    QFont yFont;
    yFont.setPointSize(8);
    m_yAxis->setTickLabelFont(yFont);
    m_yAxis->setNumberFormat("f");
    m_yAxis->setNumberPrecision(2);

    // Скрываем все остальные оси
    m_yAxisPlot->xAxis->setVisible(false);
    m_yAxisPlot->xAxis2->setVisible(false);
    m_yAxisPlot->yAxis->setVisible(false);

    // Настройка отступов
    m_yAxisPlot->axisRect()->setAutoMargins(QCP::msRight);
    m_yAxisPlot->axisRect()->setMargins(QMargins(0, 0, 0, 0));

    m_yAxisPlot->setInteractions(QCP::iNone);  // Отключаем взаимодействие

    // Поднимаем оси наверх
    m_xAxisPlot->raise();
    m_yAxisPlot->raise();
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
    finWidget->candlesticks->data().clear();
    collectCandleInfo();
    finWidget->candlesticks->setWidth(binSize*0.8); //расстояния между свечками
    finWidget->setCandlesData();
    volWidget->setCandlesData();
    volWidget->volumeBarsPositive->setWidth(binSize*0.8);
    volWidget->volumeBarsNegative->setWidth(binSize*0.8);

    volWidget->volumeBarsNegative->data().clear();
    volWidget->volumeBarsPositive->data().clear();
    for (int i=0; i<candles.size(); ++i)
    {
        long long v = candles[i].volume;
        if (candles[i].open > candles[i].close)
        {
            volWidget->volumeBarsNegative->addData(candles[i].timeCandleStart, qAbs(v));
        }
        else
        {
            volWidget->volumeBarsPositive->addData(candles[i].timeCandleStart, qAbs(v));
        }
    }

    volWidget->volumeBarsNegative->setWidth(binSize);
    volWidget->volumeBarsPositive->setWidth(binSize);

    drawPlot();
}

