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
    bool m_syncing;

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    Ui::PlotsDrawer *ui;

public slots:
    void redrawPlotByBinSizeChange_slot(uint bs);

public slots:
    void drawPlot();
    void onCandleXAxisChanged(const QCPRange &range);

};

#endif // PLOTSDRAWER_H
