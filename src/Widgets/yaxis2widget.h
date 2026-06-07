#ifndef YAXIS2WIDGET_H
#define YAXIS2WIDGET_H

#include "../qcustomplot.h"
#include <QWidget>

class YAxis2Widget : public QWidget
{
    Q_OBJECT

public:
    explicit YAxis2Widget(QWidget *parent, int width, int heigth);
    ~YAxis2Widget() {}

    QCustomPlot         *p_yAxisPlot;         // Отдельный plot для оси Y
    QCPAxis             *m_yAxis2;            // Ось Y на отдельном plot
    QLabel              *yCoordLabel;         // Метка со значением Y на оси
};

#endif // YAXIS2WIDGET_H
