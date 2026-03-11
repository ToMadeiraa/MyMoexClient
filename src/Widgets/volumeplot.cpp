#include "volumeplot.h"
#include "ui_volumeplot.h"

VolumePlot::VolumePlot(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::VolumePlot)
{
    ui->setupUi(this);
    customPlotVolume = ui->VolPlot;
}

VolumePlot::~VolumePlot()
{
    delete ui;
}

void VolumePlot::setCandlesData()
{
    volumeBarsPositive->setData(timePositive, volumePositive);
    volumeBarsNegative->setData(timeNegative, volumeNegative);
}

void VolumePlot::initPlot(double binSize, double startTime)
{
    //pos
    volumeBarsPositive = new QCPBars(customPlotVolume->xAxis, customPlotVolume->yAxis2);
    volumeBarsPositive->setBrush(QColor(100, 180, 110, 255));
    volumeBarsPositive->setWidth(0.8*binSize);//??
    volumeBarsPositive->setPen(Qt::NoPen);

    //neg
    volumeBarsNegative = new QCPBars(customPlotVolume->xAxis, customPlotVolume->yAxis2);
    volumeBarsNegative->setWidth(0.8*binSize);//??
    volumeBarsNegative->setBrush(QColor(180, 90, 90, 255));
    volumeBarsNegative->setPen(Qt::NoPen);

    QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
    dateTimeTicker->setDateTimeSpec(Qt::UTC);
    dateTimeTicker->setDateTimeFormat("dd. MM. yyyy\n hh:mm:ss");
    customPlotVolume->xAxis->setTicker(dateTimeTicker);
    customPlotVolume->xAxis->setRange(QCPRange(startTime, startTime+60));

    customPlotVolume->yAxis->setVisible(true);
    customPlotVolume->yAxis2->setVisible(true);
    customPlotVolume->xAxis->grid()->setVisible(true);
    customPlotVolume->yAxis2->grid()->setVisible(true);
    customPlotVolume->yAxis->setTickLabels(false);

    customPlotVolume->setMouseTracking(true);
}
