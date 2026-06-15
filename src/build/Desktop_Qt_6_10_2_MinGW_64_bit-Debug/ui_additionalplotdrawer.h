/********************************************************************************
** Form generated from reading UI file 'additionalplotdrawer.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDITIONALPLOTDRAWER_H
#define UI_ADDITIONALPLOTDRAWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdditionalPlotDrawer
{
public:
    QGridLayout *gridLayout;
    QWidget *widget;

    void setupUi(QWidget *AdditionalPlotDrawer)
    {
        if (AdditionalPlotDrawer->objectName().isEmpty())
            AdditionalPlotDrawer->setObjectName("AdditionalPlotDrawer");
        AdditionalPlotDrawer->resize(611, 462);
        gridLayout = new QGridLayout(AdditionalPlotDrawer);
        gridLayout->setObjectName("gridLayout");
        widget = new QWidget(AdditionalPlotDrawer);
        widget->setObjectName("widget");

        gridLayout->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(AdditionalPlotDrawer);

        QMetaObject::connectSlotsByName(AdditionalPlotDrawer);
    } // setupUi

    void retranslateUi(QWidget *AdditionalPlotDrawer)
    {
        AdditionalPlotDrawer->setWindowTitle(QCoreApplication::translate("AdditionalPlotDrawer", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AdditionalPlotDrawer: public Ui_AdditionalPlotDrawer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDITIONALPLOTDRAWER_H
