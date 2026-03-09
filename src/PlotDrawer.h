#ifndef PLOTDRAWER_H
#define PLOTDRAWER_H

#include <QObject>
#include <QDateTime>
#include "qcustomplot.h"
#include "AxisTag.h"

class Candle
{
public:
    double timeCandleStart = 0;
    double timeCandleEnd = 0;
    double open = 0;
    double high = 0;
    double low = 999999999;
    double close = 0;
    long long int volume = 0;
};

class PlotDrawer : public QWidget
{
    Q_OBJECT
public:
    PlotDrawer(QCustomPlot* cp);
    void isMouseOverBar(double x_value);
    QCustomPlot* customPlot;

    //data
    QVector<double> *priceData;
    QVector<double> *timeData;
    QVector<uint>   *quantityData;
    QVector<bool>   *buysellData;
    QVector<Candle> candles;

    //charts
    QCPFinancial *candlesticks;
    QCPAxisRect *volumeAxisRect;
    QCPBars *volumePos;
    QCPBars *volumeNeg;


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
    void initMainChart();
    void initVolChart();

public slots:
    void drawPlot();
    void setNewRange(QWheelEvent* e);
    void setNewRangeX();
    void setNewRangeY();
    void mouseMoved(QMouseEvent *e);
    void redrawPlotByBinSize_slot(uint bs);


};

inline void PlotDrawer::initMainChart()
{

}

inline void PlotDrawer::initVolChart()
{

}

#endif // PLOTDRAWER_H
