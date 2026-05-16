#include "financialwidget.h"

FinancialWidget::FinancialWidget(QWidget *parent)
    : QWidget(parent)
{
    financialPlot = new QCustomPlot(parent);
}

FinancialWidget::~FinancialWidget()
{
}

void FinancialWidget::setCandlesData()
{
    candlesticks->setData(time, open, high, low, close);
}

void FinancialWidget::initPlot(double binSize, double startTime)
{
    // customPlotFinancial->setAttribute(Qt::WA_TranslucentBackground);
    // customPlotFinancial->setFixedSize(800-70, 600-40);
    // customPlotFinancial->setGeometry(0, 0, 800-70, 600-40);
    financialPlot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // Настройка прозрачности для candle plot
    financialPlot->setBackground(QBrush(Qt::transparent));
    financialPlot->setOpenGl(false);

    // Для свечного графика разрешаем перемещение в обоих направлениях
    financialPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    financialPlot->axisRect()->setRangeDrag(Qt::Horizontal | Qt::Vertical);
    financialPlot->axisRect()->setRangeZoom(Qt::Horizontal | Qt::Vertical);

    financialPlot->axisRect()->setRangeDragAxes(financialPlot->xAxis, financialPlot->yAxis2);
    financialPlot->axisRect()->setRangeZoomAxes(financialPlot->xAxis, nullptr);  // Только X для зума

    // Поднимаем свечной график наверх
    financialPlot->raise();

    candlesticks = new QCPFinancial(financialPlot->xAxis, financialPlot->yAxis2);

    candlesticks->setName("Candles");
    candlesticks->setChartStyle(QCPFinancial::csCandlestick);
    candlesticks->setWidth(binSize*0.8); //расстояния между свечками
    candlesticks->setTwoColored(true);
    candlesticks->setBrushPositive(QColor(Qt::green));
    candlesticks->setBrushNegative(QColor(Qt::red));

    financialPlot->xAxis->setRange(QCPRange(startTime, startTime+60));
}
