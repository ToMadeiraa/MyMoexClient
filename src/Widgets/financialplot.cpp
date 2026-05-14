#include "financialplot.h"

FinancialPlot::FinancialPlot(QWidget *parent)
    : QWidget(parent)
{
    customPlotFinancial = new QCustomPlot(parent);
    customPlotFinancial->setAttribute(Qt::WA_TranslucentBackground);
    customPlotFinancial->setFixedSize(800, 600);
    customPlotFinancial->setGeometry(0, 0, 800, 600);
    // Настройка прозрачности для candle plot
    customPlotFinancial->setBackground(QBrush(Qt::transparent));
    customPlotFinancial->setOpenGl(false);











    // Настройка осей для свечного графика
    QCPAxisRect *axisRect = customPlotFinancial->axisRect();

    // === ОСЬ X (нижняя) - видимая ===
    QCPAxis *xAxis = axisRect->axis(QCPAxis::atBottom);
    xAxis->setVisible(true);
    xAxis->setTicks(true);
    xAxis->setTickLabels(true);
    xAxis->setSubTicks(true);

    // Настройка внешнего вида оси X
    xAxis->setBasePen(QPen(QColor(200, 200, 200, 180), 1));  // Светло-серая линия
    xAxis->setTickPen(QPen(QColor(200, 200, 200, 180), 1));
    xAxis->setSubTickPen(QPen(QColor(200, 200, 200, 120), 1));
    xAxis->setTickLabelColor(QColor(200, 200, 200, 200));  // Цвет подписей
    xAxis->setLabelColor(QColor(200, 200, 200, 200));

    // Настройка шрифта для подписей оси X
    QFont xFont;
    xFont.setPointSize(8);
    xAxis->setTickLabelFont(xFont);

    // Формат даты/времени для оси X
    QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
    dateTimeTicker->setDateTimeSpec(Qt::UTC);
    dateTimeTicker->setDateTimeFormat("dd. MM. yyyy\n hh:mm:ss");
    customPlotFinancial->xAxis->setTicker(dateTimeTicker);

    // Автоматический поворот подписей
    xAxis->setTickLabelRotation(0);

    // Настройка сетки оси X
    xAxis->grid()->setVisible(true);
    xAxis->grid()->setPen(QPen(QColor(200, 200, 200, 50), 1, Qt::DashLine));

    // === ОСЬ Y (левая) - скрыта ===
    QCPAxis *yAxis = axisRect->axis(QCPAxis::atLeft);
    yAxis->setVisible(false);
    yAxis->setTicks(false);
    yAxis->setTickLabels(false);
    yAxis->grid()->setVisible(false);

    // === ОСЬ Y2 (правая) - видимая ===
    QCPAxis *y2Axis = axisRect->axis(QCPAxis::atRight);
    y2Axis->setVisible(true);
    y2Axis->setTicks(true);
    y2Axis->setTickLabels(true);
    y2Axis->setSubTicks(true);

    // Настройка внешнего вида оси Y2
    y2Axis->setBasePen(QPen(QColor(200, 200, 200, 250), 1));  // Светло-серая линия
    y2Axis->setTickPen(QPen(QColor(200, 200, 200, 180), 1));
    y2Axis->setSubTickPen(QPen(QColor(200, 200, 200, 120), 1));
    y2Axis->setTickLabelColor(QColor(200, 200, 200, 200));  // Цвет подписей
    y2Axis->setLabelColor(QColor(200, 200, 200, 200));

    // Настройка шрифта для подписей оси Y2
    QFont yFont;
    yFont.setPointSize(8);
    y2Axis->setTickLabelFont(yFont);

    // Формат чисел для оси Y2
    y2Axis->setNumberFormat("f");  // Обычный формат
    y2Axis->setNumberPrecision(2);  // 2 знака после запятой

    // Настройка сетки оси Y2
    y2Axis->grid()->setVisible(true);
    y2Axis->grid()->setPen(QPen(QColor(200, 200, 200, 100), 1, Qt::DashLine));

    // === ОСЬ X2 (верхняя) - скрыта ===
    QCPAxis *x2Axis = axisRect->axis(QCPAxis::atTop);
    x2Axis->setVisible(false);
    x2Axis->setTicks(false);
    x2Axis->setTickLabels(false);
    x2Axis->grid()->setVisible(false);

    // Настройка отступов для видимых осей
    axisRect->setAutoMargins(QCP::msLeft | QCP::msRight | QCP::msBottom);
    axisRect->setMargins(QMargins(0, 0, 60, 30));  // Отступы: лево=0, верх=0, право=60, низ=30






















    // Скрываем все оси
    // QCPAxisRect *axisRect = customPlotFinancial->axisRect();

    // Убираем отступы
    // axisRect->setAutoMargins(QCP::msNone);
    // axisRect->setMargins(QMargins(0, 0, 0, 0));

    // Для свечного графика разрешаем перемещение в обоих направлениях
    customPlotFinancial->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    customPlotFinancial->axisRect()->setRangeDrag(Qt::Horizontal | Qt::Vertical);
    customPlotFinancial->axisRect()->setRangeZoom(Qt::Horizontal | Qt::Vertical);

    // Поднимаем свечной график наверх
    customPlotFinancial->raise();
}

FinancialPlot::~FinancialPlot()
{
}

void FinancialPlot::setCandlesData()
{
    candlesticks->setData(time, open, high, low, close);
}

void FinancialPlot::initPlot(double binSize, double startTime)
{
    candlesticks = new QCPFinancial(customPlotFinancial->xAxis, customPlotFinancial->yAxis);

    candlesticks->setName("Candles");
    candlesticks->setChartStyle(QCPFinancial::csCandlestick);
    candlesticks->setWidth(binSize*0.8); //расстояния между свечками
    candlesticks->setTwoColored(true);
    candlesticks->setBrushPositive(QColor(0, 215, 0));
    candlesticks->setBrushNegative(QColor(240, 0, 0));

    // QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
    // dateTimeTicker->setDateTimeSpec(Qt::UTC);
    // dateTimeTicker->setDateTimeFormat("dd. MM. yyyy\n hh:mm:ss");
    // customPlotFinancial->xAxis->setTicker(dateTimeTicker);
    customPlotFinancial->xAxis->setRange(QCPRange(startTime, startTime+60));
}
