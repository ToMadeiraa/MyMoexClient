#ifndef ADDITIONALPLOTDRAWER_H
#define ADDITIONALPLOTDRAWER_H

#include <QWidget>
#include <QGridLayout>
#include <QComboBox>
#include "../qcustomplot.h"


namespace Ui {
class AdditionalPlotDrawer;
}

class AdditionalPlotDrawer : public QWidget
{
    Q_OBJECT

public:
    explicit AdditionalPlotDrawer(QWidget *parent = nullptr);
    ~AdditionalPlotDrawer();

    QGridLayout             *p_gridLayout;
    QWidget                 *p_plotWidget;
    QComboBox               *p_comboBox;
    QCustomPlot             *p_additionalPlot;

    //sell/buy logarithmic
    QCPBars *volumeBarsPositive;
    QCPBars *volumeBarsNegative;

private:
    Ui::AdditionalPlotDrawer *ui;
};

#endif // ADDITIONALPLOTDRAWER_H
