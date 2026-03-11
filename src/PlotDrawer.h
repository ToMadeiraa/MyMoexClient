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

    double startTime;
    double binSize;
    bool autoRescale;

protected:

     bool mDraggingCustomItem;
     QPoint mDragStartPos;


public slots:
//    void setNewRange(QWheelEvent* e);


};

#endif // PLOTDRAWER_H
