#include "volumeplot.h"

VolumePlot::VolumePlot(QWidget *parent)
    : QWidget(parent)
{
    customPlotVolume = new QCustomPlot(parent);
    customPlotVolume->setFixedSize(800, 600);
    customPlotVolume->setGeometry(0, 0, 800, 600);
    customPlotVolume->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    customPlotVolume->setBackground(QBrush(Qt::transparent));
    customPlotVolume->axisRect()->setBackground(QBrush(Qt::transparent));
    customPlotVolume->setOpenGl(false);
    customPlotVolume->setInteractions(QCP::iNone);

    // Скрываем все оси
    QCPAxisRect *axisRect = customPlotVolume->axisRect();

    QList<QCPAxis::AxisType> axisTypes = {
        QCPAxis::atLeft, QCPAxis::atRight,
        QCPAxis::atTop, QCPAxis::atBottom
    };

    for (QCPAxis::AxisType type : axisTypes)
    {
        QCPAxis *axis = axisRect->axis(type);
        axis->setVisible(false);
        axis->setTicks(false);
        axis->setTickLabels(false);
        axis->grid()->setVisible(true);
        axis->grid()->setPen(QPen(Qt::transparent));
        axis->setSubTicks(false);
        axis->setTickPen(QPen(Qt::transparent));
        axis->setSubTickPen(QPen(Qt::transparent));
        axis->setBasePen(QPen(Qt::transparent));
        axis->setLabel("");
    }
    // Убираем отступы
    // axisRect->setAutoMargins(QCP::msNone);
    // axisRect->setMargins(QMargins(0, 0, 0, 0));

    // Настройка отступов для видимых осей
    axisRect->setAutoMargins(QCP::msLeft | QCP::msRight | QCP::msBottom);
    axisRect->setMargins(QMargins(0, 0, 60, 30));  // Отступы: лево=0, верх=0, право=60, низ=30

    // Запрещаем перемещение по Y для volume plot
    customPlotVolume->axisRect()->setRangeDrag(Qt::Horizontal);  // Только горизонтальное перемещение
    customPlotVolume->axisRect()->setRangeZoom(Qt::Horizontal);  // Только горизонтальный зум
}

VolumePlot::~VolumePlot()
{
}

void VolumePlot::setCandlesData()
{
    volumeBarsPositive->setData(timePositive, volumePositive);
    volumeBarsNegative->setData(timeNegative, volumeNegative);
}

void VolumePlot::initPlot(double binSize, double startTime)
{
    //pos
    volumeBarsPositive = new QCPBars(customPlotVolume->xAxis, customPlotVolume->yAxis2);
    volumeBarsPositive->setBrush(QColor(100, 180, 110, 255));
    volumeBarsPositive->setWidth(0.8*binSize);
    volumeBarsPositive->setPen(Qt::NoPen);

    //neg
    volumeBarsNegative = new QCPBars(customPlotVolume->xAxis, customPlotVolume->yAxis2);
    volumeBarsNegative->setWidth(0.8*binSize);
    volumeBarsNegative->setBrush(QColor(180, 90, 90, 255));
    volumeBarsNegative->setPen(Qt::NoPen);

    // QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
    // dateTimeTicker->setDateTimeSpec(Qt::UTC);
    // dateTimeTicker->setDateTimeFormat("dd. MM. yyyy\n hh:mm:ss");
    // customPlotVolume->xAxis->setTicker(dateTimeTicker);
    customPlotVolume->xAxis->setRange(QCPRange(startTime, startTime+60));
}
