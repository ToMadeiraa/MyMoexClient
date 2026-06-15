#include "verticalvolumewidget.h"

VerticalVolumeWidget::VerticalVolumeWidget(QWidget *parent, int width, int heigth)
    : QWidget(parent)
{
    volumePlot = new QCustomPlot(parent);
    volumePlot->setMinimumSize(width, heigth);
    // volumePlot->setGeometry(0, 0, width, heigth);
    volumePlot->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
}

VerticalVolumeWidget::~VerticalVolumeWidget()
{
}

void VerticalVolumeWidget::setCandlesData()
{
    volumeBarsPositive->setData(timePositive, volumePositive);
    volumeBarsNegative->setData(timeNegative, volumeNegative);
}

void VerticalVolumeWidget::initPlot(double binSize, double startTime)
{
    volumePlot->setBackground(QBrush(Qt::transparent));
    volumePlot->axisRect()->setBackground(QBrush(Qt::transparent));
    volumePlot->setOpenGl(false);
    volumePlot->setInteractions(QCP::iNone);

    // Запрещаем перемещение по Y для volume plot
    volumePlot->axisRect()->setRangeDrag(Qt::Horizontal);
    volumePlot->axisRect()->setRangeZoom(Qt::Horizontal);

    //Позитивные значения
    volumeBarsPositive = new QCPBars(volumePlot->xAxis, volumePlot->yAxis2);
    volumeBarsPositive->setBrush(QColor(Qt::darkGreen));
    volumeBarsPositive->setWidth(0.8*binSize);
    volumeBarsPositive->setPen(Qt::NoPen);

    //Негативные значения
    volumeBarsNegative = new QCPBars(volumePlot->xAxis, volumePlot->yAxis2);
    volumeBarsNegative->setWidth(0.8*binSize);
    volumeBarsNegative->setBrush(QColor(Qt::darkRed));
    volumeBarsNegative->setPen(Qt::NoPen);

    volumePlot->xAxis->setRange(QCPRange(startTime, startTime+60));
}
