#ifndef HORIZONTALVOLUMEWIDGET_H
#define HORIZONTALVOLUMEWIDGET_H

#include "../qcustomplot.h"
#include <QWidget>

class HorizontalVolumeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HorizontalVolumeWidget(QWidget *parent, int width, int heigth);

    QCustomPlot     *p_volumePlot;
    QCPBars         *p_volumeBars;

    QVector<double> m_price;
    QVector<double> m_volume;

    void setCandlesData();
    void initPlot(double binSize, double startTime);
};


#endif // HORIZONTALVOLUMEWIDGET_H
