/********************************************************************************
** Form generated from reading UI file 'plotsdrawer.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOTSDRAWER_H
#define UI_PLOTSDRAWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <Widgets/financialplot.h>
#include <Widgets/volumeplot.h>

QT_BEGIN_NAMESPACE

class Ui_PlotsDrawer
{
public:
    QVBoxLayout *verticalLayout;
    FinancialPlot *PlotWidgetCandlesticks;
    VolumePlot *PlotWidgetVolume;

    void setupUi(QWidget *PlotsDrawer)
    {
        if (PlotsDrawer->objectName().isEmpty())
            PlotsDrawer->setObjectName("PlotsDrawer");
        PlotsDrawer->resize(736, 548);
        verticalLayout = new QVBoxLayout(PlotsDrawer);
        verticalLayout->setObjectName("verticalLayout");
        PlotWidgetCandlesticks = new FinancialPlot(PlotsDrawer);
        PlotWidgetCandlesticks->setObjectName("PlotWidgetCandlesticks");

        verticalLayout->addWidget(PlotWidgetCandlesticks);

        PlotWidgetVolume = new VolumePlot(PlotsDrawer);
        PlotWidgetVolume->setObjectName("PlotWidgetVolume");

        verticalLayout->addWidget(PlotWidgetVolume);


        retranslateUi(PlotsDrawer);

        QMetaObject::connectSlotsByName(PlotsDrawer);
    } // setupUi

    void retranslateUi(QWidget *PlotsDrawer)
    {
        PlotsDrawer->setWindowTitle(QCoreApplication::translate("PlotsDrawer", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PlotsDrawer: public Ui_PlotsDrawer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOTSDRAWER_H
