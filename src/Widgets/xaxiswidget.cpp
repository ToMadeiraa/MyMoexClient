#include "xaxiswidget.h"

XAxisWidget::XAxisWidget(QWidget *parent, int width, int heigth)
    : QWidget(parent)
{
    p_xAxisPlot = new QCustomPlot(parent);

    p_xAxisPlot->setAttribute(Qt::WA_TranslucentBackground);
    p_xAxisPlot->setFixedSize(width, heigth);
    p_xAxisPlot->setBackground(QBrush(QColor(0, 0, 0, 80)));  // Полупрозрачный фон
    p_xAxisPlot->setOpenGl(false);

    m_xAxis = p_xAxisPlot->xAxis;
    m_xAxis->setVisible(true);
    m_xAxis->setTicks(true);
    m_xAxis->setTickLabels(true);
    m_xAxis->setSubTicks(true);

    // Внешний вид оси X
    m_xAxis->setBasePen(QPen(QColor(200, 200, 200, 150), 2));
    m_xAxis->setTickPen(QPen(QColor(200, 200, 200, 200), 1));
    m_xAxis->setSubTickPen(QPen(QColor(200, 200, 200, 150), 1));
    m_xAxis->setTickLabelColor(QColor(220, 220, 220, 230));

    QFont xFont;
    xFont.setPointSize(8);
    m_xAxis->setTickLabelFont(xFont);

    // Скрываем все остальные оси
    p_xAxisPlot->yAxis->setVisible(false);
    p_xAxisPlot->xAxis2->setVisible(false);
    p_xAxisPlot->yAxis2->setVisible(false);

    // Настройка отступов
    p_xAxisPlot->axisRect()->setAutoMargins(QCP::msBottom);
    p_xAxisPlot->axisRect()->setMargins(QMargins(0, 0, 0, 0));

    p_xAxisPlot->setInteractions(QCP::iNone);  // Отключаем взаимодействие

    QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
    dateTimeTicker->setDateTimeSpec(Qt::UTC);
    dateTimeTicker->setDateTimeFormat("dd. MM. yyyy\n hh:mm:ss");
    dateTimeTicker->setTickCount(8);
    m_xAxis->setTicker(dateTimeTicker);

    // Включаем взаимодействие для оси X (только горизонтальное)
    p_xAxisPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    p_xAxisPlot->axisRect()->setRangeDrag(Qt::Horizontal);
    p_xAxisPlot->axisRect()->setRangeZoom(Qt::Horizontal);
    p_xAxisPlot->axisRect()->setRangeDragAxes(p_xAxisPlot->xAxis, nullptr);
    p_xAxisPlot->axisRect()->setRangeZoomAxes(p_xAxisPlot->xAxis, nullptr);

    //creating value labels
    xCoordLabel = new QLabel(parent);
    xCoordLabel->setFixedSize(100,heigth);
    xCoordLabel->setText("");
    xCoordLabel->setAlignment(Qt::AlignCenter);
    xCoordLabel->setAutoFillBackground(true);
    xCoordLabel->move(-1000, 20);
}
