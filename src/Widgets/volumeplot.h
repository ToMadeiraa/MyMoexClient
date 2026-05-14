#ifndef VOLUMEPLOT_H
#define VOLUMEPLOT_H

#include "../qcustomplot.h"
#include <QWidget>

class VolumePlot : public QWidget
{
    Q_OBJECT

public:
    explicit VolumePlot(QWidget *parent = nullptr);
    ~VolumePlot();

    QCustomPlot* customPlotVolume;
    QCPBars *volumeBarsPositive;
    QCPBars *volumeBarsNegative;

    //for volume
    QVector<double> timePositive;
    QVector<double> volumePositive;
    QVector<double> timeNegative;
    QVector<double> volumeNegative;

    void setCandlesData();
    void initPlot(double binSize, double startTime);
};

#endif // VOLUMEPLOT_H
