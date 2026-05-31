#ifndef XAXISWIDGET_H
#define XAXISWIDGET_H

#include "../qcustomplot.h"
#include <QWidget>

class XAxisWidget : public QWidget
{
    Q_OBJECT

public:
    explicit XAxisWidget(QWidget *parent, int width, int heigth);
    ~XAxisWidget() {}

    QCustomPlot         *p_xAxisPlot;         // Отдельный plot для оси X
    QCPAxis             *m_xAxis;             // Ось X на отдельном plot
};

#endif // XAXISWIDGET_H
