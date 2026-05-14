#ifndef VOLUMEWIDGET_H
#define VOLUMEWIDGET_H

#include "../qcustomplot.h"
#include <QWidget>

class VolumeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VolumeWidget(QWidget *parent = nullptr);
    ~VolumeWidget();

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

#endif // VOLUMEWIDGET_H
