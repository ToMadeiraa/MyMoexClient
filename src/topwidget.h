#ifndef TOPWIDGET_H
#define TOPWIDGET_H

#include <QWidget>
#include "GuiElements/mycomboboxbinsize.h"
#include "GuiElements/mycomboboxsecurity.h"

namespace Ui {
class TopWidget;
}

class TopWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TopWidget(QWidget *parent = nullptr);
    ~TopWidget();

    MyComboBoxSecurity *getComboBoxSecurities();
    MyComboBoxBinSize *getComboBoxBinSize();
    QComboBox* getComboBoxIndicators();

private:
    Ui::TopWidget *ui;
};

#endif // TOPWIDGET_H
