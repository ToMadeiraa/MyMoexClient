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
    double volume = 0;
};

class PlotDrawer : public QWidget
{
    Q_OBJECT
public:
    PlotDrawer(QCustomPlot* cp);
    void isMouseOverBar(double x_value);
    void collectCandleInfo();

    QCustomPlot* customPlot;

    //data
    QVector<double> *priceData;
    QVector<double> *timeData;
    QVector<uint>   *quantityData;
    QVector<bool>   *buysellData;


    QVector<Candle> candles;
    QVector<double> open;
    QVector<double> high;
    QVector<double> low;
    QVector<double> close;
    QVector<double> time;

    //for volume
    QVector<double> timePositive;
    QVector<double> volumePositive;
    QVector<double> timeNegative;
    QVector<double> volumeNegative;


    //charts
    QCPFinancial *candlesticks;
    QCPBars *volumeBarsPositive;
    QCPBars *volumeBarsNegative;

    QCPItemStraightLine *infLine;
    AxisTag *mTag1;
    QCPFinancialDataContainer dataContainer;

    QDateTime start;
    double startTime;
    double binSize;

    bool autoRescale;

protected:
    void mousePressEvent(QMouseEvent *event) override;

    bool mDraggingCustomItem;
    QPoint mDragStartPos;

private:
    void initMainChart();
    void initVolChart();

public slots:
    void drawPlot();
    void setNewRange(QWheelEvent* e);
    void mouseMoved(QMouseEvent *e);
    void mousePressed(QMouseEvent *e);
    void mouseReleased(QMouseEvent *e);
    void redrawPlotByBinSizeChange_slot(uint bs);

};

#endif // PLOTDRAWER_H
