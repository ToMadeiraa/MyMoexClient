#include "additionalplotdrawer.h"
#include "ui_additionalplotdrawer.h"

AdditionalPlotDrawer::AdditionalPlotDrawer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AdditionalPlotDrawer)
{
    ui->setupUi(this);
    p_gridLayout = new QGridLayout(ui->widget);
    p_comboBox = new QComboBox();
    p_additionalPlot = new QCustomPlot();
    p_gridLayout->addWidget(p_comboBox, 0, 0);
    p_gridLayout->addWidget(p_additionalPlot, 1, 0);
    p_gridLayout->setRowStretch(0,1);
    p_gridLayout->setRowStretch(1,1);

    // p_additionalPlot->setFixedSize(width, heigth);
    // p_additionalPlot->setGeometry(0, 0, width, heigth);
    p_additionalPlot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    volumeBarsPositive = new QCPBars(p_additionalPlot->xAxis, p_additionalPlot->yAxis);
    volumeBarsPositive->setBrush(QColor(Qt::darkGreen));
    volumeBarsPositive->setPen(Qt::NoPen);

    volumeBarsNegative = new QCPBars(p_additionalPlot->xAxis, p_additionalPlot->yAxis2);
    volumeBarsNegative->setBrush(QColor(Qt::darkRed));
    volumeBarsNegative->setPen(Qt::NoPen);

    p_comboBox->addItem("Логарифмический график объема покупки/продажи");
}

AdditionalPlotDrawer::~AdditionalPlotDrawer()
{
    delete ui;
}
