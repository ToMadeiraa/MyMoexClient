#include "candleswidget.h"

CandlesWidget::CandlesWidget(QWidget *parent, int width, int heigth)
    : QWidget(parent)
{
    financialPlot = new QCustomPlot(parent);
    financialPlot->setFixedSize(width, heigth);
    financialPlot->setGeometry(0, 0, width, heigth);
    financialPlot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

CandlesWidget::~CandlesWidget()
{
}

void CandlesWidget::setCandlesData()
{
    candlesticks->setData(time, open, high, low, close);
}

void CandlesWidget::initPlot(double binSize, double startTime)
{
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
