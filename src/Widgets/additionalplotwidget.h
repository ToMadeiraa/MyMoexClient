#ifndef ADDITIONALPLOTWIDGET_H
#define ADDITIONALPLOTWIDGET_H

#include <QWidget>
#include "../qcustomplot.h"

class AdditionalPlotWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AdditionalPlotWidget(QWidget *parent, int width, int heigth);

    QCustomPlot     *p_AdditionalPlot;
    void initPlot(double binSize, double startTime);
};

#endif // ADDITIONALPLOTWIDGET_H
