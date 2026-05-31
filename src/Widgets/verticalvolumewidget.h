#ifndef VERTICALVOLUMEWIDGET_H
#define VERTICALVOLUMEWIDGET_H

#include "../qcustomplot.h"
#include <QWidget>

class VerticalVolumeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VerticalVolumeWidget(QWidget *parent, int width, int heigth);
    ~VerticalVolumeWidget();

    QCustomPlot* volumePlot;
    QCPBars *volumeBarsPositive;
    QCPBars *volumeBarsNegative;

    QVector<double> timePositive;
    QVector<double> volumePositive;
    QVector<double> timeNegative;
    QVector<double> volumeNegative;

    void setCandlesData();
    void initPlot(double binSize, double startTime);
};

#endif // VERTICALVOLUMEWIDGET_H
