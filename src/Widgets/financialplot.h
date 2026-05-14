#ifndef FINANCIALPLOT_H
#define FINANCIALPLOT_H

#include <QWidget>
#include "../qcustomplot.h"
#include "../AxisTag.h"

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

class FinancialPlot : public QWidget
{
    Q_OBJECT

public:
    explicit FinancialPlot(QWidget *parent = nullptr);
    ~FinancialPlot();

    QCustomPlot* customPlotFinancial;
    QCPFinancial *candlesticks;

    QVector<double> open;
    QVector<double> high;
    QVector<double> low;
    QVector<double> close;
    QVector<double> time;

    QCPItemStraightLine *infLine;

    void setCandlesData();
    void initPlot(double binSize, double startTime);
};

#endif // FINANCIALPLOT_H
