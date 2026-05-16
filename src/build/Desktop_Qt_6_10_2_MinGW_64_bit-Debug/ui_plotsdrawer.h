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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlotsDrawer
{
public:
    QGridLayout *gridLayout;
    QGridLayout *gridPlotsLayout;
    QWidget *y2AxisWidget;
    QWidget *PlotsWidget;
    QWidget *xAxisWidget;

    void setupUi(QWidget *PlotsDrawer)
    {
        if (PlotsDrawer->objectName().isEmpty())
            PlotsDrawer->setObjectName("PlotsDrawer");
        PlotsDrawer->resize(800, 600);
        gridLayout = new QGridLayout(PlotsDrawer);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridPlotsLayout = new QGridLayout();
        gridPlotsLayout->setObjectName("gridPlotsLayout");
        y2AxisWidget = new QWidget(PlotsDrawer);
        y2AxisWidget->setObjectName("y2AxisWidget");
        y2AxisWidget->setMinimumSize(QSize(70, 0));

        gridPlotsLayout->addWidget(y2AxisWidget, 0, 1, 1, 1);

        PlotsWidget = new QWidget(PlotsDrawer);
        PlotsWidget->setObjectName("PlotsWidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PlotsWidget->sizePolicy().hasHeightForWidth());
        PlotsWidget->setSizePolicy(sizePolicy);

        gridPlotsLayout->addWidget(PlotsWidget, 0, 0, 1, 1);

        xAxisWidget = new QWidget(PlotsDrawer);
        xAxisWidget->setObjectName("xAxisWidget");
        xAxisWidget->setMinimumSize(QSize(0, 40));

        gridPlotsLayout->addWidget(xAxisWidget, 1, 0, 1, 1);


        gridLayout->addLayout(gridPlotsLayout, 0, 0, 1, 1);


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
