#include "horizontalvolumewidget.h"

HorizontalVolumeWidget::HorizontalVolumeWidget(QWidget *parent, int width, int heigth)
: QWidget(parent)
{
    p_volumePlot = new QCustomPlot(parent);
    p_volumePlot->setFixedSize(width, heigth);
    p_volumePlot->setGeometry(0, 0, width, heigth);
    p_volumePlot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

void HorizontalVolumeWidget::setCandlesData()
{
    p_volumeBars->setData(m_price, m_volume);
}

void HorizontalVolumeWidget::initPlot(double binSize, double startTime)
{
    p_volumePlot->setBackground(QBrush(Qt::transparent));
    p_volumePlot->axisRect()->setBackground(QBrush(Qt::transparent));
    p_volumePlot->setOpenGl(false);
    p_volumePlot->setInteractions(QCP::iNone);

    // Запрещаем перемещение по Y для volume plot
    p_volumePlot->axisRect()->setRangeDrag(Qt::Vertical);
    p_volumePlot->axisRect()->setRangeZoom(Qt::Vertical);

    p_volumeBars = new QCPBars(p_volumePlot->yAxis2, p_volumePlot->xAxis);
    p_volumeBars->setBrush(QColor(Qt::darkGreen));
    p_volumeBars->setWidth(0.01*binSize);
    p_volumeBars->setPen(Qt::NoPen);

    p_volumePlot->xAxis->setRange(QCPRange(startTime, startTime+60));
}
