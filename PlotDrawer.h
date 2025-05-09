#ifndef PLOTDRAWER_H
#define PLOTDRAWER_H

#include  <QObject>
#include <QDateTime>

#include "qcustomplot.h"

class PlotDrawer : public QObject
{
    Q_OBJECT
public:
    PlotDrawer(QCustomPlot* cp);
    QCustomPlot* customPlot;

    QVector<double> *priceData;
    QVector<double> *timeData;
    QVector<double> time, value;

    QCPFinancial *candlesticks;
    QDateTime start;
    double startTime;
    double binSize;

public slots:

    void drawPlot();
};

#endif // PLOTDRAWER_H
