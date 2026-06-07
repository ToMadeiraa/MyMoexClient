#include "plotsdrawer.h"
#include "ui_plotsdrawer.h"

PlotsDrawer::PlotsDrawer(QWidget *parent)
    : QWidget(parent)
    , m_binSize(60) //интервал в секундах
    , m_syncing(false)
    , ui(new Ui::PlotsDrawer)
{
    ui->setupUi(this);

    m_startDateTime = QDateTime(QDate(2026, 1, 1), QTime(9,59,50));
    m_startDateTime.setTimeSpec(Qt::UTC);
    m_doubleStartDateTime = m_startDateTime.currentSecsSinceEpoch();

    //creating bottom plot (for horizontal volumes for example)
    p_horizontalVolumeWidget = new HorizontalVolumeWidget(ui->PlotsWidget, WINDOW_WIDTH - Y_AXIS_WIDTH, WINDOW_HEIGHT - X_AXIS_HEIGHT);
    p_horizontalVolumeWidget->initPlot(m_binSize, m_doubleStartDateTime);
    hideAllAxes(p_horizontalVolumeWidget->p_volumePlot);

    //creating vertical volume plot
    p_verticalVolumeWidget = new VerticalVolumeWidget(ui->PlotsWidget, WINDOW_WIDTH - Y_AXIS_WIDTH, WINDOW_HEIGHT - X_AXIS_HEIGHT);
    p_verticalVolumeWidget->initPlot(m_binSize, m_doubleStartDateTime);
    hideAllAxes(p_verticalVolumeWidget->volumePlot);

    //creating candles plot
    p_candlesWidget = new CandlesWidget(ui->PlotsWidget, WINDOW_WIDTH - Y_AXIS_WIDTH, WINDOW_HEIGHT - X_AXIS_HEIGHT);
    p_candlesWidget->initPlot(m_binSize, m_doubleStartDateTime);
    p_candlesWidget->financialPlot->installEventFilter(this);
    hideAllAxes(p_candlesWidget->financialPlot);

    p_xAxisWidget = new XAxisWidget(ui->xAxisWidget, WINDOW_WIDTH, X_AXIS_HEIGHT);
    p_yAxis2Widget = new YAxis2Widget(ui->y2AxisWidget, Y_AXIS_WIDTH, WINDOW_HEIGHT);

    ui->PlotsWidget->setFixedSize(WINDOW_WIDTH - Y_AXIS_WIDTH, WINDOW_HEIGHT - X_AXIS_HEIGHT);
    ui->y2AxisWidget->setFixedSize(Y_AXIS_WIDTH, WINDOW_HEIGHT - X_AXIS_HEIGHT);
    ui->xAxisWidget->setFixedSize(WINDOW_WIDTH - Y_AXIS_WIDTH, X_AXIS_HEIGHT);

    m_palette = new QPalette;
    m_palette->setColor(QPalette::Window, Qt::white);
    m_palette->setColor(QPalette::WindowText, Qt::black);
    p_xAxisWidget->xCoordLabel->setPalette(*m_palette);
    p_yAxis2Widget->yCoordLabel->setPalette(*m_palette);

    createPlotConnections();
}

PlotsDrawer::~PlotsDrawer()
{
    delete ui;
}

void PlotsDrawer::drawPlot()
{
    if (p_priceData->isEmpty() || p_timeData->isEmpty()) return;

    p_horizontalVolumeWidget->p_volumePlot->rescaleAxes(true);
    p_verticalVolumeWidget->volumePlot->rescaleAxes(true);
    p_candlesWidget->financialPlot->rescaleAxes(true);

    p_candlesWidget->financialPlot->replot();

    //делаем так, чтоб график объемов занимал 20%
    QCPRange autoRangeVertical = p_verticalVolumeWidget->volumePlot->yAxis2->range();
    p_verticalVolumeWidget->volumePlot->yAxis2->setRange(autoRangeVertical.lower, autoRangeVertical.upper * 5);
    p_verticalVolumeWidget->volumePlot->replot();

    //делаем так, чтоб график объемов занимал 20%
    QCPRange autoRangeHorizontalX = p_horizontalVolumeWidget->p_volumePlot->xAxis->range();
    p_horizontalVolumeWidget->p_volumePlot->xAxis->setRange(autoRangeHorizontalX.lower, autoRangeHorizontalX.upper * 5);
    p_horizontalVolumeWidget->p_volumeBars->setWidth((yAxis2MaxValue-yAxis2MinValue)/HORIZONTAL_BARS_NUMBER*0.8);
    p_horizontalVolumeWidget->p_volumePlot->replot();
}

void PlotsDrawer::onCandleXAxisChanged(const QCPRange &range)
{
    if (m_syncing) return;

    m_syncing = true;

    p_verticalVolumeWidget->volumePlot->xAxis->setRange(range);
    p_verticalVolumeWidget->volumePlot->replot();

    m_syncing = false;
}


void PlotsDrawer::onXAxisPlotRangeChanged(const QCPRange &range)
{
    if (m_syncing) return;

    m_syncing = true;

    // Синхронизируем все графики с новым диапазоном X
    p_candlesWidget->financialPlot->xAxis->setRange(range);
    p_verticalVolumeWidget->volumePlot->xAxis->setRange(range);

    p_candlesWidget->financialPlot->replot();
    p_verticalVolumeWidget->volumePlot->replot();

    m_syncing = false;
}

void PlotsDrawer::onYAxisPlotRangeChanged(const QCPRange &range)
{
    if (m_syncing) return;

    m_syncing = true;

    // Синхронизируем все графики с новым диапазоном X
    p_candlesWidget->financialPlot->yAxis2->setRange(range);
    p_candlesWidget->financialPlot->replot();

    p_horizontalVolumeWidget->p_volumePlot->yAxis2->setRange(range);
    p_horizontalVolumeWidget->p_volumePlot->replot();

    m_syncing = false;
}

void PlotsDrawer::syncAxesToCandleX(const QCPRange &range)
{
    if (m_syncing) return;

    m_syncing = true;

    // Синхронизируем ось X на отдельном plot'е
    p_xAxisWidget->p_xAxisPlot->xAxis->setRange(range);
    p_xAxisWidget->p_xAxisPlot->replot();

    m_syncing = false;
}

void PlotsDrawer::syncAxesToCandleY(const QCPRange &range)
{
    if (m_syncing) return;

    m_syncing = true;

    // Синхронизируем ось Y на отдельном plot'е
    p_yAxis2Widget->p_yAxisPlot->yAxis2->setRange(range);
    p_yAxis2Widget->p_yAxisPlot->replot();

    p_horizontalVolumeWidget->p_volumePlot->yAxis2->setRange(range);
    p_horizontalVolumeWidget->p_volumePlot->replot();


    m_syncing = false;
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
    // Синхронизация оси X графиков financialPlot и volumePlot
    connect(p_candlesWidget->financialPlot->xAxis,
            QOverload<const QCPRange &>::of(&QCPAxis::rangeChanged),
            this, &PlotsDrawer::onCandleXAxisChanged);

    // Синхронизация оси X основного графика с осевым plot
    connect(p_candlesWidget->financialPlot->xAxis,
            QOverload<const QCPRange &>::of(&QCPAxis::rangeChanged),
            this, &PlotsDrawer::syncAxesToCandleX);

    // Синхронизация оси Y основного графика с осевым plot'ом
    connect(p_candlesWidget->financialPlot->yAxis2,
            QOverload<const QCPRange &>::of(&QCPAxis::rangeChanged),
            this, &PlotsDrawer::syncAxesToCandleY);

    // Добавляем обработку колеса мыши для оси X
    connect(p_xAxisWidget->p_xAxisPlot->xAxis,
            QOverload<const QCPRange &>::of(&QCPAxis::rangeChanged),
            this, &PlotsDrawer::onXAxisPlotRangeChanged);

    // Добавляем обработку колеса мыши для оси Y
    connect(p_yAxis2Widget->p_yAxisPlot->yAxis2,
            QOverload<const QCPRange &>::of(&QCPAxis::rangeChanged),
            this, &PlotsDrawer::onYAxisPlotRangeChanged);

    // Устанавливаем фильтры событий
    p_xAxisWidget->p_xAxisPlot->installEventFilter(this);
    p_yAxis2Widget->p_yAxisPlot->installEventFilter(this);
    p_xAxisWidget->xCoordLabel->installEventFilter(this);
    p_yAxis2Widget->yCoordLabel->installEventFilter(this);
}

QLabel *PlotsDrawer::getLabelOpen(){return ui->labelOpen;}
QLabel *PlotsDrawer::getLabelHigh(){return ui->labelHigh;}
QLabel *PlotsDrawer::getLabelLow(){return ui->labelLow;}
QLabel *PlotsDrawer::getLabelClose(){return ui->labelClose;}
QLabel *PlotsDrawer::getLabelChange(){return ui->labelChange;}
QLabel *PlotsDrawer::getLabelVolumeVertical(){return ui->labelVerticalVolume;}
QLabel *PlotsDrawer::getLabelVolumeHorizontal(){return ui->labelHorizontalVolume;}


void PlotsDrawer::redrawPlotByBinSizeChange_slot(uint bs)
{
    m_binSize = bs;
    p_candlesWidget->candlesticks->data().clear();
    collectCandleInfo();
    p_candlesWidget->candlesticks->setWidth(m_binSize*0.8); //расстояния между свечками
    p_candlesWidget->setCandlesData();
    p_verticalVolumeWidget->setCandlesData();
    p_horizontalVolumeWidget->setCandlesData();

    p_verticalVolumeWidget->volumeBarsNegative->data().clear();
    p_verticalVolumeWidget->volumeBarsPositive->data().clear();
    p_horizontalVolumeWidget->p_volumeBars->data().clear();
    for (int i=0; i < m_candles.size(); ++i)
    {
        long long v = m_candles[i].volume;
        if (m_candles[i].open > m_candles[i].close)
        {
            p_verticalVolumeWidget->volumeBarsNegative->addData(m_candles[i].timeCandleStart, qAbs(v));
        }
        else
        {
            p_verticalVolumeWidget->volumeBarsPositive->addData(m_candles[i].timeCandleStart, qAbs(v));
        }
    }

    p_verticalVolumeWidget->volumeBarsNegative->setWidth(m_binSize);
    p_verticalVolumeWidget->volumeBarsPositive->setWidth(m_binSize);

    drawPlot();
}

void PlotsDrawer::clearSecurityData()
{
    p_timeData->clear();
    p_priceData->clear();
    p_quantityData->clear();
    p_buysellData->clear();
    p_candlesWidget->candlesticks->data().clear();
}


void PlotsDrawer::collectCandleInfo()
{
    m_candles.clear();
    Candle c;
    double previousTime = p_timeData->first();
    c.timeCandleStart = previousTime;
    c.open = p_priceData->first();
    for (long long int i = 0; i < p_timeData->size(); ++i)
    {
        double currentPrice = p_priceData->at(i);
        c.high = std::max(c.high, currentPrice);
        c.low = std::min(c.low, currentPrice);
        c.volume += p_quantityData->at(i);
        if (p_timeData->at(i) - previousTime > m_binSize)
        {
            c.timeCandleEnd = p_timeData->at(i);
            c.close = currentPrice;
            m_candles.push_back(c);
            //at least one more candle
            if (i != p_timeData->size()-1)
            {
                previousTime = p_timeData->at(i+1);
                c.timeCandleStart = previousTime;
                c.open = currentPrice;
                c.high = 0;
                c.low = INT_MAX;
                c.close = 0;
                c.volume = 0;
            }
        }
    }

    p_candlesWidget->open.clear();
    p_candlesWidget->high.clear();
    p_candlesWidget->low.clear();
    p_candlesWidget->close.clear();
    p_candlesWidget->time.clear();

    p_candlesWidget->open.resize(m_candles.size());
    p_candlesWidget->high.resize(m_candles.size());
    p_candlesWidget->low.resize(m_candles.size());
    p_candlesWidget->close.resize(m_candles.size());
    p_candlesWidget->time.resize(m_candles.size());

    //for vertical volume
    p_verticalVolumeWidget->volumePositive.clear();
    p_verticalVolumeWidget->timePositive.clear();
    p_verticalVolumeWidget->volumeNegative.clear();
    p_verticalVolumeWidget->timeNegative.clear();

    p_verticalVolumeWidget->volumePositive.resize(m_candles.size());
    p_verticalVolumeWidget->timePositive.resize(m_candles.size());
    p_verticalVolumeWidget->volumeNegative.resize(m_candles.size());
    p_verticalVolumeWidget->timeNegative.resize(m_candles.size());


    for (int i = 0; i < m_candles.size(); ++i)
    {
        p_candlesWidget->open[i] = m_candles[i].open;
        p_candlesWidget->high[i] = m_candles[i].high;
        p_candlesWidget->low[i] = m_candles[i].low;
        p_candlesWidget->close[i] = m_candles[i].close;
        p_candlesWidget->time[i] = m_candles[i].timeCandleStart;

        //for volume
        if (m_candles[i].open > m_candles[i].close)
        {
            p_verticalVolumeWidget->timeNegative[i] = m_candles[i].timeCandleStart;
            p_verticalVolumeWidget->volumeNegative[i] = m_candles[i].volume;

            p_verticalVolumeWidget->timePositive[i] = m_candles[i].timeCandleStart;
            p_verticalVolumeWidget->volumePositive[i] = 0;
        }
        else
        {
            p_verticalVolumeWidget->timeNegative[i] = m_candles[i].timeCandleStart;
            p_verticalVolumeWidget->volumeNegative[i] = 0;

            p_verticalVolumeWidget->timePositive[i] = m_candles[i].timeCandleStart;
            p_verticalVolumeWidget->volumePositive[i] = m_candles[i].volume;
        }
    }

    //for horizontal volume
    yAxis2MaxValue = 0;
    yAxis2MinValue = INT_MAX;
    for (int i = 0; i < m_candles.size(); ++i)
    {
        if (m_candles[i].high > yAxis2MaxValue)
            yAxis2MaxValue = m_candles[i].high;
        if (m_candles[i].low < yAxis2MinValue)
            yAxis2MinValue = m_candles[i].low;
    }

    p_horizontalVolumeWidget->m_price.clear();
    p_horizontalVolumeWidget->m_volume.clear();
    p_horizontalVolumeWidget->m_price.resize(HORIZONTAL_BARS_NUMBER);
    p_horizontalVolumeWidget->m_volume.resize(HORIZONTAL_BARS_NUMBER);

    double priceStep = (yAxis2MaxValue-yAxis2MinValue)/(HORIZONTAL_BARS_NUMBER-1);

    for (int i = 0; i < HORIZONTAL_BARS_NUMBER; ++i)
        p_horizontalVolumeWidget->m_price[i] = yAxis2MinValue + priceStep/2 + priceStep*i;

    yAxis2MinValue -= EPSILON;

    for (long long int i = 0; i < p_timeData->size(); ++i)
    {
        double currValue = p_priceData->at(i);
        ushort j = abs(currValue - yAxis2MinValue)/priceStep;
        p_horizontalVolumeWidget->m_volume[j] += p_quantityData->at(i);
    }
}

bool PlotsDrawer::eventFilter(QObject *obj, QEvent *event)
{
    // Перехватываем события колеса мыши
    if (event->type() == QEvent::Wheel)
    {
        QWheelEvent *wheelEvent = static_cast<QWheelEvent*>(event);

        // Проверяем, что событие от свечного графика
        if (obj == p_candlesWidget->financialPlot)
        {
            // Получаем текущий диапазон X
            QCPRange xRange = p_candlesWidget->financialPlot->xAxis->range();
            double center = xRange.center();
            double range = xRange.size();

            // Коэффициент масштабирования
            double scaleFactor = 1.15;

            // Определяем направление прокрутки
            if (wheelEvent->angleDelta().y() < 0)
            {
                range *= scaleFactor;
            }
            else
            {
                range /= scaleFactor;
            }

            // Устанавливаем новый диапазон X
            QCPRange newRange(center - range / 2.0, center + range / 2.0);

            m_syncing = true;
            p_candlesWidget->financialPlot->xAxis->setRange(newRange);
            p_verticalVolumeWidget->volumePlot->xAxis->setRange(newRange);
            p_xAxisWidget->p_xAxisPlot->xAxis->setRange(newRange);
            p_candlesWidget->financialPlot->replot();
            p_verticalVolumeWidget->volumePlot->replot();
            p_xAxisWidget->p_xAxisPlot->replot();
            m_syncing = false;
        }


        // Обработка колеса мыши на xAxisPlot
        if (obj == p_xAxisWidget->p_xAxisPlot || obj == p_xAxisWidget->xCoordLabel)
        {
            // Получаем текущий диапазон X с оси X plot
            QCPRange xRange = p_xAxisWidget->p_xAxisPlot->xAxis->range();
            double center = xRange.center();
            double range = xRange.size();

            double scaleFactor = 1.15;

            if (wheelEvent->angleDelta().y() < 0)
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
            p_xAxisWidget->p_xAxisPlot->xAxis->setRange(newRange);
            p_candlesWidget->financialPlot->xAxis->setRange(newRange);
            p_verticalVolumeWidget->volumePlot->xAxis->setRange(newRange);

            p_xAxisWidget->p_xAxisPlot->replot();
            p_candlesWidget->financialPlot->replot();
            p_verticalVolumeWidget->volumePlot->replot();

            m_syncing = false;
        }


        // Обработка колеса мыши на yAxisPlot
        if (obj == p_yAxis2Widget->p_yAxisPlot || obj == p_yAxis2Widget->yCoordLabel)
        {
            // Получаем текущий диапазон X с оси X plot
            QCPRange yRange = p_yAxis2Widget->p_yAxisPlot->yAxis2->range();
            double center = yRange.center();
            double range = yRange.size();

            double scaleFactor = 1.15;

            if (wheelEvent->angleDelta().y() < 0)
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
            p_yAxis2Widget->p_yAxisPlot->yAxis2->setRange(newRange);
            p_candlesWidget->financialPlot->yAxis2->setRange(newRange);
            p_horizontalVolumeWidget->p_volumePlot->yAxis2->setRange(newRange); //new

            p_yAxis2Widget->p_yAxisPlot->replot();
            p_candlesWidget->financialPlot->replot();
            p_horizontalVolumeWidget->p_volumePlot->replot(); //new

            m_syncing = false;
        }

        //
        mouseMoveEvent(obj, event);
        return true;
    }

    if (event->type() == QEvent::MouseMove)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

        int pixelX = mouseEvent->pos().x();
        int pixelY = mouseEvent->pos().y();

        double time = p_candlesWidget->financialPlot->xAxis->pixelToCoord(pixelX) + m_binSize/2;
        double price = p_candlesWidget->financialPlot->yAxis2->pixelToCoord(pixelY);
        double verticalVolume = 0;
        double horizontalVolume = 0;
        double priceOpen = 0;
        double priceClose = 0;
        double priceHigh = 0;
        double priceLow = 0;

        for (int i = 0; i < m_candles.size(); ++i)
        {
            if (m_candles[i].timeCandleStart <= time && m_candles[i].timeCandleEnd >= time)
            {
                priceOpen = m_candles[i].open;
                priceClose = m_candles[i].close;
                priceHigh = m_candles[i].high;
                priceLow = m_candles[i].low;
                verticalVolume = m_candles[i].volume;
                break;
            }
        }

        double minDiff = INT_MAX;
        int currVolIndex = 0;
        for (int i = 0; i < p_horizontalVolumeWidget->m_price.size(); ++i)
        {
            if (abs(p_horizontalVolumeWidget->m_price[i] - price) < minDiff)
            {
                minDiff = abs(p_horizontalVolumeWidget->m_price[i] - price);
                currVolIndex = i;
            }
        }
        horizontalVolume = p_horizontalVolumeWidget->m_volume[currVolIndex];

        getLabelOpen()->setText(QString::number(priceOpen, 'g', 8));
        getLabelClose()->setText(QString::number(priceClose, 'g', 8));
        getLabelHigh()->setText(QString::number(priceHigh, 'g', 8));
        getLabelLow()->setText(QString::number(priceLow, 'g', 8));
        getLabelVolumeVertical()->setText(QString::number(verticalVolume, 'g', 8));
        getLabelVolumeHorizontal()->setText(QString::number(horizontalVolume, 'g', 8));


        //горизонтальная и вертикальная линии
        double xValue = p_candlesWidget->financialPlot->xAxis->pixelToCoord(mouseEvent->pos().x());
        double yValue = p_candlesWidget->financialPlot->yAxis2->pixelToCoord(mouseEvent->pos().y());

        // Получаем границы видимой области
        auto xRange = p_candlesWidget->financialPlot->xAxis->range();
        auto yRange = p_candlesWidget->financialPlot->yAxis2->range();

        if (p_candlesWidget->financialPlot->axisRect()->rect().contains(mouseEvent->pos()))
        {
            // Вертикальная линия (продлеваем за ось X вниз)
            p_candlesWidget->lineX->point1->setCoords(xValue, yRange.lower);  // Уходим за ось X
            p_candlesWidget->lineX->point2->setCoords(xValue, yRange.upper);

            // Горизонтальная линия (продлеваем за ось Y2 вправо)
            p_candlesWidget->lineY->point1->setCoords(xRange.lower, yValue);
            p_candlesWidget->lineY->point2->setCoords(xRange.upper, yValue);  // Уходим за ось Y2

            // Показываем все элементы
            p_candlesWidget->lineX->setVisible(true);
            p_candlesWidget->lineY->setVisible(true);

            // Обновляем текст метки
            QDateTime dateTimeUtc = QDateTime::fromSecsSinceEpoch(static_cast<qint64>(xValue), Qt::UTC);
            p_xAxisWidget->xCoordLabel->setText(dateTimeUtc.toString("dd. MM. yyyy\n hh:mm:ss"));
            p_yAxis2Widget->yCoordLabel->setText(QString::number(yValue));

            // Устанавливаем позицию меток

            p_xAxisWidget->xCoordLabel->move(mouseEvent->pos().x() - p_xAxisWidget->xCoordLabel->geometry().width()/2, 0);
            p_yAxis2Widget->yCoordLabel->move(0, mouseEvent->pos().y() - p_yAxis2Widget->yCoordLabel->geometry().height()/2);
        }
        else
        {
            // Скрываем линии и метки, если курсор за пределами графика
            p_candlesWidget->lineX->setVisible(false);
            p_candlesWidget->lineY->setVisible(false);
        }

        p_candlesWidget->financialPlot->replot();
    }

    return false;
}

bool PlotsDrawer::mouseMoveEvent(QObject *obj, QEvent *event)
{
    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

    int pixelX = mouseEvent->pos().x();
    int pixelY = mouseEvent->pos().y();

    double time = p_candlesWidget->financialPlot->xAxis->pixelToCoord(pixelX) + m_binSize/2;
    double price = p_candlesWidget->financialPlot->yAxis2->pixelToCoord(pixelY);
    double verticalVolume = 0;
    double horizontalVolume = 0;
    double priceOpen = 0;
    double priceClose = 0;
    double priceHigh = 0;
    double priceLow = 0;

    for (int i = 0; i < m_candles.size(); ++i)
    {
        if (m_candles[i].timeCandleStart <= time && m_candles[i].timeCandleEnd >= time)
        {
            priceOpen = m_candles[i].open;
            priceClose = m_candles[i].close;
            priceHigh = m_candles[i].high;
            priceLow = m_candles[i].low;
            verticalVolume = m_candles[i].volume;
            break;
        }
    }

    double minDiff = INT_MAX;
    int currVolIndex = 0;
    for (int i = 0; i < p_horizontalVolumeWidget->m_price.size(); ++i)
    {
        if (abs(p_horizontalVolumeWidget->m_price[i] - price) < minDiff)
        {
            minDiff = abs(p_horizontalVolumeWidget->m_price[i] - price);
            currVolIndex = i;
        }
    }
    horizontalVolume = p_horizontalVolumeWidget->m_volume[currVolIndex];

    getLabelOpen()->setText(QString::number(priceOpen, 'g', 8));
    getLabelClose()->setText(QString::number(priceClose, 'g', 8));
    getLabelHigh()->setText(QString::number(priceHigh, 'g', 8));
    getLabelLow()->setText(QString::number(priceLow, 'g', 8));
    getLabelVolumeVertical()->setText(QString::number(verticalVolume, 'g', 8));
    getLabelVolumeHorizontal()->setText(QString::number(horizontalVolume, 'g', 8));


    //горизонтальная и вертикальная линии
    double xValue = p_candlesWidget->financialPlot->xAxis->pixelToCoord(mouseEvent->pos().x());
    double yValue = p_candlesWidget->financialPlot->yAxis2->pixelToCoord(mouseEvent->pos().y());

    // Получаем границы видимой области
    auto xRange = p_candlesWidget->financialPlot->xAxis->range();
    auto yRange = p_candlesWidget->financialPlot->yAxis2->range();

    if (p_candlesWidget->financialPlot->axisRect()->rect().contains(mouseEvent->pos()))
    {
        // Вертикальная линия (продлеваем за ось X вниз)
        p_candlesWidget->lineX->point1->setCoords(xValue, yRange.lower);  // Уходим за ось X
        p_candlesWidget->lineX->point2->setCoords(xValue, yRange.upper);

        // Горизонтальная линия (продлеваем за ось Y2 вправо)
        p_candlesWidget->lineY->point1->setCoords(xRange.lower, yValue);
        p_candlesWidget->lineY->point2->setCoords(xRange.upper, yValue);  // Уходим за ось Y2

        // Показываем все элементы
        p_candlesWidget->lineX->setVisible(true);
        p_candlesWidget->lineY->setVisible(true);

        // Обновляем текст метки
        QDateTime dateTimeUtc = QDateTime::fromSecsSinceEpoch(static_cast<qint64>(xValue), Qt::UTC);
        p_xAxisWidget->xCoordLabel->setText(dateTimeUtc.toString("dd. MM. yyyy\n hh:mm:ss"));
        p_yAxis2Widget->yCoordLabel->setText(QString::number(yValue));

        // Устанавливаем позицию меток

        p_xAxisWidget->xCoordLabel->move(mouseEvent->pos().x() - p_xAxisWidget->xCoordLabel->geometry().width()/2, 0);
        p_yAxis2Widget->yCoordLabel->move(0, mouseEvent->pos().y() - p_yAxis2Widget->yCoordLabel->geometry().height()/2);
    }
    else
    {
        // Скрываем линии и метки, если курсор за пределами графика
        p_candlesWidget->lineX->setVisible(false);
        p_candlesWidget->lineY->setVisible(false);
    }

    p_candlesWidget->financialPlot->replot();
}

