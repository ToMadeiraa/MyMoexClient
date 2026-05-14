#ifndef PLOTSDRAWER_H
#define PLOTSDRAWER_H

#include <QWidget>
#include "Widgets/financialwidget.h"
#include "Widgets/volumewidget.h"

namespace Ui {
class PlotsDrawer;
}

class PlotsDrawer : public QWidget
{
    Q_OBJECT

public:
    explicit PlotsDrawer(QWidget *parent = nullptr);
    ~PlotsDrawer();

    QVector<Candle> candles;
    QVector<double> *priceData;
    QVector<double> *timeData;
    QVector<uint>   *quantityData;
    QVector<bool>   *buysellData;

    QDateTime start;
    double startTime;
    double binSize;

    FinancialWidget* finWidget;
    VolumeWidget* volWidget;
    QCustomPlot *m_xAxisPlot;         // Отдельный plot для оси X
    QCustomPlot *m_yAxisPlot;         // Отдельный plot для оси Y
    QCPAxis *m_xAxis;                 // Ось X на отдельном plot
    QCPAxis *m_yAxis;                 // Ось Y на отдельном plot

    void isMouseOverBar(double x_value);
    void clearSecurityData();
    void collectCandleInfo();
    bool m_syncing;

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    void hideAllAxes(QCustomPlot *plot);
    void createPlotConnections();
    void setupAxisPlots();

    static const int WINDOW_WIDTH = 800;
    static const int WINDOW_HEIGHT = 600;
    static const int X_AXIS_HEIGHT = 40;
    static const int Y_AXIS_WIDTH = 70;

    Ui::PlotsDrawer *ui;

public slots:
    void redrawPlotByBinSizeChange_slot(uint bs);

public slots:
    void drawPlot();
    void onCandleXAxisChanged(const QCPRange &range);
    void onCandleYAxisChanged(const QCPRange &range);
    void onXAxisPlotRangeChanged(const QCPRange &range);
    void syncAxesToCandleX(const QCPRange &range);
    void syncAxesToCandleY(const QCPRange &range);

};

#endif // PLOTSDRAWER_H
