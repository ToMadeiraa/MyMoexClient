#include "yaxis2widget.h"

YAxis2Widget::YAxis2Widget(QWidget *parent, int width, int heigth)
    : QWidget(parent)
{
    // === Y AXIS PLOT (справа) ===
    p_yAxisPlot = new QCustomPlot(parent);
    p_yAxisPlot->setAttribute(Qt::WA_TranslucentBackground);
    p_yAxisPlot->setFixedSize(width, heigth);

    p_yAxisPlot->setBackground(QBrush(QColor(0, 0, 0, 80)));  // Полупрозрачный фон
    p_yAxisPlot->setOpenGl(false);

    // Настройка оси Y (справа)
    m_yAxis2 = p_yAxisPlot->yAxis2;
    m_yAxis2->setVisible(true);
    m_yAxis2->setTicks(true);
    m_yAxis2->setTickLabels(true);
    m_yAxis2->setSubTicks(true);

    // Внешний вид оси Y
    m_yAxis2->setBasePen(QPen(QColor(200, 200, 200, 220), 2));
    m_yAxis2->setTickPen(QPen(QColor(200, 200, 200, 200), 1));
    m_yAxis2->setSubTickPen(QPen(QColor(200, 200, 200, 150), 1));
    m_yAxis2->setTickLabelColor(QColor(220, 220, 220, 230));

    QFont yFont;
    yFont.setPointSize(8);
    m_yAxis2->setTickLabelFont(yFont);
    m_yAxis2->setNumberFormat("f");
    m_yAxis2->setNumberPrecision(2);

    // Скрываем все остальные оси
    p_yAxisPlot->xAxis->setVisible(false);
    p_yAxisPlot->xAxis2->setVisible(false);
    p_yAxisPlot->yAxis->setVisible(false);

    // Настройка отступов
    p_yAxisPlot->axisRect()->setAutoMargins(QCP::msRight);
    p_yAxisPlot->axisRect()->setMargins(QMargins(0, 0, 0, 0));

    // Включаем взаимодействие для оси Y (только вертикальная)
    p_yAxisPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    p_yAxisPlot->axisRect()->setRangeDrag(Qt::Vertical);
    p_yAxisPlot->axisRect()->setRangeZoom(Qt::Vertical);
    p_yAxisPlot->axisRect()->setRangeDragAxes(nullptr, p_yAxisPlot->yAxis2);
    p_yAxisPlot->axisRect()->setRangeZoomAxes(nullptr, p_yAxisPlot->yAxis2);

    //creating value labels
    yCoordLabel = new QLabel(parent);
    yCoordLabel->setText("");
    yCoordLabel->move(15, -1000);
    yCoordLabel->setFixedSize(width,30);
    yCoordLabel->setAlignment(Qt::AlignCenter);
    yCoordLabel->setAutoFillBackground(true);
}
