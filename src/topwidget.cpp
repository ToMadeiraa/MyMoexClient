#include "topwidget.h"
#include "ui_topwidget.h"

TopWidget::TopWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TopWidget)
{
    ui->setupUi(this);
}

TopWidget::~TopWidget()
{
    delete ui;
}

MyComboBoxSecurity *TopWidget::getComboBoxSecurities()
{
    return ui->comboBoxSecurities;
}

MyComboBoxBinSize *TopWidget::getComboBoxBinSize()
{
    return ui->comboBoxBinSize;
}
