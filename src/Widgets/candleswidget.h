#ifndef CANDLESWIDGET_H
#define CANDLESWIDGET_H

#include <QWidget>
#include "../qcustomplot.h"

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

class CandlesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CandlesWidget(QWidget *parent, int width, int heigth);
    ~CandlesWidget();

    QCustomPlot* financialPlot;
    QCPFinancial *candlesticks;

    QVector<double> open;
    QVector<double> high;
    QVector<double> low;
    QVector<double> close;
    QVector<double> time;

    QCPItemStraightLine *lineX;
    QCPItemStraightLine *lineY;

    void setCandlesData();
    void initPlot(double binSize, double startTime);
};

#endif // CANDLESWIDGET_H
