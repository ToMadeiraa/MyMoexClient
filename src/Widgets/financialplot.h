#ifndef FINANCIALPLOT_H
#define FINANCIALPLOT_H

#include <QWidget>
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

namespace Ui {
class FinancialPlot;
}

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
    AxisTag *mTag1;

    void setCandlesData();
    void initPlot(double binSize, double startTime);

private:
    Ui::FinancialPlot *ui;
};

#endif // FINANCIALPLOT_H
