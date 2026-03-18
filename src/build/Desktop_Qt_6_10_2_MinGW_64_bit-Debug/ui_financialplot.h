/********************************************************************************
** Form generated from reading UI file 'financialplot.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINANCIALPLOT_H
#define UI_FINANCIALPLOT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_FinancialPlot
{
public:
    QHBoxLayout *horizontalLayout;
    QCustomPlot *FinPlot;

    void setupUi(QWidget *FinancialPlot)
    {
        if (FinancialPlot->objectName().isEmpty())
            FinancialPlot->setObjectName("FinancialPlot");
        FinancialPlot->resize(827, 287);
        horizontalLayout = new QHBoxLayout(FinancialPlot);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        FinPlot = new QCustomPlot(FinancialPlot);
        FinPlot->setObjectName("FinPlot");

        horizontalLayout->addWidget(FinPlot);


        retranslateUi(FinancialPlot);

        QMetaObject::connectSlotsByName(FinancialPlot);
    } // setupUi

    void retranslateUi(QWidget *FinancialPlot)
    {
        FinancialPlot->setWindowTitle(QCoreApplication::translate("FinancialPlot", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FinancialPlot: public Ui_FinancialPlot {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINANCIALPLOT_H
