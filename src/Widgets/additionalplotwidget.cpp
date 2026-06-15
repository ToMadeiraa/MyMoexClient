#include "additionalplotwidget.h"

AdditionalPlotWidget::AdditionalPlotWidget(QWidget *parent, int width, int heigth)
    : QWidget(parent)
{
    p_AdditionalPlot = new QCustomPlot(parent);
    p_AdditionalPlot->setMinimumSize(width, heigth);
    // p_AdditionalPlot->setGeometry(0, 0, width, heigth);
    p_AdditionalPlot->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
}

void AdditionalPlotWidget::initPlot(double binSize, double startTime)
{
    p_AdditionalPlot->setBackground(QBrush(Qt::transparent));
    p_AdditionalPlot->axisRect()->setBackground(QBrush(Qt::transparent));
    p_AdditionalPlot->setOpenGl(false);
    p_AdditionalPlot->setInteractions(QCP::iNone);

    // Запрещаем перемещение по Y для volume plot
    p_AdditionalPlot->axisRect()->setRangeDrag(Qt::Vertical);
    p_AdditionalPlot->axisRect()->setRangeZoom(Qt::Vertical);

    p_AdditionalPlot->xAxis->setRange(QCPRange(startTime, startTime+60));
}
