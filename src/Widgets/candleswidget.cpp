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

    // Создаем вертикальную линию (для оси X)
    lineX = new QCPItemStraightLine(financialPlot);
    lineX->setPen(QPen(Qt::darkGray, 1, Qt::DashLine));
    lineX->point1->setCoords(0, -1);
    lineX->point2->setCoords(0, 1);
    lineX->point1->setAxes(financialPlot->xAxis, financialPlot->yAxis2);
    lineX->point2->setAxes(financialPlot->xAxis, financialPlot->yAxis2);
    lineX->setClipToAxisRect(false);  // Продолжаем линию до оси

    // Создаем горизонтальную линию (для оси Y)
    lineY = new QCPItemStraightLine(financialPlot);
    lineY->setPen(QPen(Qt::darkGray, 1, Qt::DashLine));
    lineY->point1->setCoords(-1, 0);
    lineY->point2->setCoords(1, 0);
    lineY->point1->setAxes(financialPlot->xAxis, financialPlot->yAxis2);
    lineY->point2->setAxes(financialPlot->xAxis, financialPlot->yAxis2);
    lineY->setClipToAxisRect(false);  // Продолжаем линию до оси
}
