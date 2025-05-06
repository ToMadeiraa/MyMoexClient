#ifndef PLOTDRAWER_H
#define PLOTDRAWER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include "qcustomplot.h"

class PlotDrawer
{
public:
    PlotDrawer();
    QCustomPlot* customPlot;

    void drawPlot();
};

#endif // PLOTDRAWER_H
