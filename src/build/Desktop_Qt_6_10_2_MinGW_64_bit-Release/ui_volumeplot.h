/********************************************************************************
** Form generated from reading UI file 'volumeplot.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VOLUMEPLOT_H
#define UI_VOLUMEPLOT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_VolumePlot
{
public:
    QHBoxLayout *horizontalLayout;
    QCustomPlot *VolPlot;

    void setupUi(QWidget *VolumePlot)
    {
        if (VolumePlot->objectName().isEmpty())
            VolumePlot->setObjectName("VolumePlot");
        VolumePlot->resize(610, 300);
        horizontalLayout = new QHBoxLayout(VolumePlot);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        VolPlot = new QCustomPlot(VolumePlot);
        VolPlot->setObjectName("VolPlot");

        horizontalLayout->addWidget(VolPlot);


        retranslateUi(VolumePlot);

        QMetaObject::connectSlotsByName(VolumePlot);
    } // setupUi

    void retranslateUi(QWidget *VolumePlot)
    {
        VolumePlot->setWindowTitle(QCoreApplication::translate("VolumePlot", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VolumePlot: public Ui_VolumePlot {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VOLUMEPLOT_H
