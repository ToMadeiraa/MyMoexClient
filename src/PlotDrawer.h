#ifndef PLOTDRAWER_H
#define PLOTDRAWER_H

#include <QObject>
#include <QDateTime>

#include <algorithm>
#include "qcustomplot.h"
#include "AxisTag.h"

class Candle
{
public:
    double timeCandleStart = 0;
    double timeCandleEnd = 0;
    double open = 0;
    double high = 0;
    double low = 0;
    double close = 0;
};

class PlotDrawer : public QWidget
{
    Q_OBJECT
public:
    PlotDrawer(QCustomPlot* cp);
    bool isMouseOverBar(double x_value);
    QCustomPlot* customPlot;

    QVector<double> *priceData;
    QVector<double> *timeData;
    QVector<uint>   *quantityData;
    QVector<bool>   *buysellData;
    QVector<Candle> candles;

    QCPFinancial *candlesticks;
    QCPItemStraightLine *infLine;
    AxisTag *mTag1;
    QCPFinancialDataContainer dataContainer;

    QDateTime start;
    double startTime;
    double binSize;

    bool autoRescale;

private:
    bool isXAxisChosen;
    bool isYAxisChosen;
    void collectCandleInfo();

public slots:
    void drawPlot();
    void setNewRange(QWheelEvent* e);
    void setNewRangeX();
    void setNewRangeY();
    void mouseMoved(QMouseEvent *e);
    void redrawPlotByBinSize_slot(uint bs);


};

#endif // PLOTDRAWER_H
