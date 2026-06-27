#ifndef PLOTSDRAWER_H
#define PLOTSDRAWER_H

#define WINDOW_WIDTH            800
#define WINDOW_HEIGHT           600
#define X_AXIS_HEIGHT           40
#define Y_AXIS_WIDTH            50
#define HORIZONTAL_BARS_NUMBER  50
#define EPSILON                 std::numeric_limits<double>::epsilon()

#include "ui_plotsdrawer.h"

#include <QWidget>
#include "Widgets/candleswidget.h"
#include "Widgets/verticalvolumewidget.h"
#include "Widgets/horizontalvolumewidget.h"
#include "Widgets/xaxiswidget.h"
#include "Widgets/yaxis2widget.h"

namespace Ui {
class PlotsDrawer;
}

class PlotsDrawer : public QWidget
{
    Q_OBJECT

public:
    explicit PlotsDrawer(QWidget *parent = nullptr);
    ~PlotsDrawer();

    void clearSecurityData();
    void collectCandleInfo();

    QDateTime               m_startDateTime;
    double                  m_doubleStartDateTime;
    double                  m_binSize;

    QVector<Candle>         m_candles;
    QVector<double>         *p_priceData;
    QVector<double>         *p_timeData;
    QVector<uint>           *p_quantityData;
    QVector<bool>           *p_buysellData;

    QHBoxLayout             *p_horizontalLayout;
    QVBoxLayout             *p_verticalLayout;
    QGridLayout             *p_gridLayout;
    QLabel                  *p_labelOpen;
    QLabel                  *p_labelHigh;
    QLabel                  *p_labelLow;
    QLabel                  *p_labelClose;
    QLabel                  *p_labelChange;
    QLabel                  *p_labelVerticalVolume;
    QLabel                  *p_labelHorizontalVolume;

    CandlesWidget           *p_candlesWidget;
    VerticalVolumeWidget    *p_verticalVolumeWidget;
    HorizontalVolumeWidget  *p_horizontalVolumeWidget;

    XAxisWidget             *p_xAxisWidget;
    YAxis2Widget            *p_yAxis2Widget;

    QWidget                 *p_plotsWidget;
    QWidget                 *p_xWidget;
    QWidget                 *p_yWidget;

    QPalette                *m_palette;

    bool                    m_syncing;
    double                  yAxis2MinValue;
    double                  yAxis2MaxValue;
    double                  xAxisMinValue;
    double                  xAxisMaxValue;

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    bool mouseMoveEvent(QObject *obj, QEvent *event);
    void resizeEvent(QResizeEvent *event) override;

private:
    void hideAllAxes(QCustomPlot *plot);
    void createPlotConnections();

    Ui::PlotsDrawer *ui;

public slots:
    void drawPlot();
    void redrawPlotByBinSizeChange_slot(uint bs);
    void onCandleXAxisChanged(const QCPRange &range);
    void onXAxisPlotRangeChanged(const QCPRange &range);
    void onYAxisPlotRangeChanged(const QCPRange &range);
    void syncAxesToCandleX(const QCPRange &range);
    void syncAxesToCandleY(const QCPRange &range);

};

#endif // PLOTSDRAWER_H
