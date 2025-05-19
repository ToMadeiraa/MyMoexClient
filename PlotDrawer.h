#ifndef PLOTDRAWER_H
#define PLOTDRAWER_H

#include <QObject>
#include <QDateTime>

#include "qcustomplot.h"

class PlotDrawer : public QWidget
{
    Q_OBJECT
public:
    PlotDrawer(QCustomPlot* cp);
    QCustomPlot* customPlot;

    QVector<double> *priceData;
    QVector<double> *timeData;

    QCPFinancial *candlesticks;
    QDateTime start;
    double startTime;
    double binSize;

    bool autoRescale;

public slots:
    void drawPlot();
    void setNewRange(QWheelEvent* e);
    void setNewRangeX();


};

#endif // PLOTDRAWER_H
