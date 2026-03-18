#ifndef PLOTSDRAWER_H
#define PLOTSDRAWER_H

#include <QWidget>
#include "Widgets/financialplot.h"
#include "Widgets/volumeplot.h"

namespace Ui {
class PlotsDrawer;
}

class PlotsDrawer : public QWidget
{
    Q_OBJECT

public:
    explicit PlotsDrawer(QWidget *parent = nullptr);
    ~PlotsDrawer();

    //data
    QVector<Candle> candles;
    QVector<double> *priceData;
    QVector<double> *timeData;
    QVector<uint>   *quantityData;
    QVector<bool>   *buysellData;

    QDateTime start;
    double startTime;
    double binSize;
    bool autoRescale;

    FinancialPlot* finPlot;
    VolumePlot* volPlot;
    void isMouseOverBar(double x_value);
    void clearSecurityData();
    void collectCandleInfo();

private:
    Ui::PlotsDrawer *ui;
    bool m_dragging;
    bool m_rangeChangedLock;
    QPoint m_lastDragPos;

    void connectSignals();
    void syncPlotRanges();

public slots:
    void mouseMoved(QMouseEvent *e);
    void mousePressed(QMouseEvent *e);
    void mouseReleased(QMouseEvent *e);
    void redrawPlotByBinSizeChange_slot(uint bs);

public slots:
    void drawPlot();

private slots:
    void onHorizontalRangeChanged(const QCPRange &newRange);
    void onVerticalRangeChanged(const QCPRange &newRange);
    void onMouseWheel();
    void onMousePress();
    void onMouseMove();
    void onMouseRelease();

};

#endif // PLOTSDRAWER_H
