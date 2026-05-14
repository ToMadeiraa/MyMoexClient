#ifndef FINANCIALWIDGET_H
#define FINANCIALWIDGET_H

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

class FinancialWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FinancialWidget(QWidget *parent = nullptr);
    ~FinancialWidget();

    QCustomPlot* financialPlot;
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

#endif // FINANCIALWIDGET_H
