#ifndef PLOTDRAWER_H
#define PLOTDRAWER_H

#include <QObject>
#include <QDateTime>

#include "qcustomplot.h"
#include "AxisTag.h"

class PlotDrawer : public QWidget
{
    Q_OBJECT
public:
    PlotDrawer(QCustomPlot* cp);
    QCustomPlot* customPlot;

    QVector<double> *priceData;
    QVector<double> *timeData;

    QCPFinancial *candlesticks;
    QCPItemStraightLine *infLine;
    AxisTag *mTag1;

    QDateTime start;
    double startTime;
    double binSize;

    bool autoRescale;

private:
    bool isXAxisChosen;
    bool isYAxisChosen;

public slots:
    void drawPlot();
    void setNewRange(QWheelEvent* e);
    void setNewRangeX();
    void setNewRangeY();
    void mouseMoved(QMouseEvent *e);


};

#endif // PLOTDRAWER_H
