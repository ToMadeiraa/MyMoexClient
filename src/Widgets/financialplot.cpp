#include "financialplot.h"
#include "ui_financialplot.h"

FinancialPlot::FinancialPlot(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FinancialPlot)
{
    ui->setupUi(this);
}

FinancialPlot::~FinancialPlot()
{
    delete ui;
}

void FinancialPlot::setCandlesData()
{
    candlesticks->setData(time, open, high, low, close);
}

void FinancialPlot::initPlot(double binSize, double startTime)
{
    customPlotFinancial = ui->FinPlot;
    candlesticks = new QCPFinancial(customPlotFinancial->xAxis, customPlotFinancial->yAxis2);

    candlesticks->setName("Candles");
    candlesticks->setChartStyle(QCPFinancial::csCandlestick);
    candlesticks->setWidth(binSize*0.8); //расстояния между свечками
    candlesticks->setTwoColored(true);
    candlesticks->setBrushPositive(QColor(0, 215, 0));
    candlesticks->setBrushNegative(QColor(240, 0, 0));

    QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
    dateTimeTicker->setDateTimeSpec(Qt::UTC);
    dateTimeTicker->setDateTimeFormat("dd. MM. yyyy\n hh:mm:ss");
    customPlotFinancial->xAxis->setTicker(dateTimeTicker);
    customPlotFinancial->xAxis->setRange(QCPRange(startTime, startTime+60));
    //customPlotFinancial->xAxis->scaleRange(1.025, customPlotFinancial->xAxis->range().center());
    // customPlot->yAxis->scaleRange(1.1, customPlot->yAxis2->range().center());
    //customPlotFinancial->yAxis2->scaleRange(1.1, customPlotFinancial->yAxis2->range().center());


    //customPlotFinancial->axisRect()->axis(QCPAxis::atRight, 0)->setPadding(30); // add some padding to have space for tags
    //customPlot->axisRect()->axis(QCPAxis::atRight, 1)->setPadding(30); // add some padding to have space for tags

    //QList<QCPAxis *> draggableAxes = {customPlotFinancial->xAxis,customPlotFinancial->yAxis2};
    //QList<QCPAxis *> zoomableAxes = {customPlotFinancial->xAxis,customPlotFinancial->yAxis2};
    //customPlotFinancial->axisRect()->setRangeDragAxes(draggableAxes);
    //customPlotFinancial->axisRect()->setRangeZoomAxes(zoomableAxes);

    customPlotFinancial->yAxis->setVisible(true);
    customPlotFinancial->yAxis2->setVisible(true);
    customPlotFinancial->xAxis->grid()->setVisible(true);
    customPlotFinancial->yAxis2->grid()->setVisible(true);
    customPlotFinancial->yAxis->setTickLabels(false);

    // create tags with newly introduced AxisTag class (see axistag.h/.cpp):
    mTag1 = new AxisTag(candlesticks->valueAxis());
    mTag1->setPen(candlesticks->pen());

    infLine = new QCPItemStraightLine(customPlotFinancial);

    customPlotFinancial->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    customPlotFinancial->setMouseTracking(true);
}
