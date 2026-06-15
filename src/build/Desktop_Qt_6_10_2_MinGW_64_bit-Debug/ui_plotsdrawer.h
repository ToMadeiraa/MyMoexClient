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
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlotsDrawer
{
public:
    QGridLayout *gridLayout;
    QGridLayout *gridPlotsLayout;
    QWidget *y2AxisWidget;
    QWidget *xAxisWidget;
    QWidget *PlotsWidget;
    QGridLayout *labelsLayout;
    QLabel *labelChange;
    QLabel *labelHigh;
    QLabel *labelVerticalVolume;
    QLabel *labelOpen;
    QLabel *labelClose;
    QLabel *labelLow;
    QLabel *labelHorizontalVolume;

    void setupUi(QWidget *PlotsDrawer)
    {
        if (PlotsDrawer->objectName().isEmpty())
            PlotsDrawer->setObjectName("PlotsDrawer");
        PlotsDrawer->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PlotsDrawer->sizePolicy().hasHeightForWidth());
        PlotsDrawer->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(PlotsDrawer);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridPlotsLayout = new QGridLayout();
        gridPlotsLayout->setObjectName("gridPlotsLayout");
        y2AxisWidget = new QWidget(PlotsDrawer);
        y2AxisWidget->setObjectName("y2AxisWidget");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(y2AxisWidget->sizePolicy().hasHeightForWidth());
        y2AxisWidget->setSizePolicy(sizePolicy1);
        y2AxisWidget->setMinimumSize(QSize(70, 0));

        gridPlotsLayout->addWidget(y2AxisWidget, 1, 1, 1, 1);

        xAxisWidget = new QWidget(PlotsDrawer);
        xAxisWidget->setObjectName("xAxisWidget");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(xAxisWidget->sizePolicy().hasHeightForWidth());
        xAxisWidget->setSizePolicy(sizePolicy2);
        xAxisWidget->setMinimumSize(QSize(0, 40));

        gridPlotsLayout->addWidget(xAxisWidget, 2, 0, 1, 1);

        PlotsWidget = new QWidget(PlotsDrawer);
        PlotsWidget->setObjectName("PlotsWidget");
        sizePolicy.setHeightForWidth(PlotsWidget->sizePolicy().hasHeightForWidth());
        PlotsWidget->setSizePolicy(sizePolicy);

        gridPlotsLayout->addWidget(PlotsWidget, 1, 0, 1, 1);

        labelsLayout = new QGridLayout();
        labelsLayout->setObjectName("labelsLayout");
        labelChange = new QLabel(PlotsDrawer);
        labelChange->setObjectName("labelChange");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(labelChange->sizePolicy().hasHeightForWidth());
        labelChange->setSizePolicy(sizePolicy3);

        labelsLayout->addWidget(labelChange, 0, 4, 1, 1);

        labelHigh = new QLabel(PlotsDrawer);
        labelHigh->setObjectName("labelHigh");
        sizePolicy3.setHeightForWidth(labelHigh->sizePolicy().hasHeightForWidth());
        labelHigh->setSizePolicy(sizePolicy3);

        labelsLayout->addWidget(labelHigh, 0, 1, 1, 1);

        labelVerticalVolume = new QLabel(PlotsDrawer);
        labelVerticalVolume->setObjectName("labelVerticalVolume");
        sizePolicy3.setHeightForWidth(labelVerticalVolume->sizePolicy().hasHeightForWidth());
        labelVerticalVolume->setSizePolicy(sizePolicy3);

        labelsLayout->addWidget(labelVerticalVolume, 0, 5, 1, 1);

        labelOpen = new QLabel(PlotsDrawer);
        labelOpen->setObjectName("labelOpen");
        sizePolicy3.setHeightForWidth(labelOpen->sizePolicy().hasHeightForWidth());
        labelOpen->setSizePolicy(sizePolicy3);

        labelsLayout->addWidget(labelOpen, 0, 0, 1, 1);

        labelClose = new QLabel(PlotsDrawer);
        labelClose->setObjectName("labelClose");
        sizePolicy3.setHeightForWidth(labelClose->sizePolicy().hasHeightForWidth());
        labelClose->setSizePolicy(sizePolicy3);

        labelsLayout->addWidget(labelClose, 0, 3, 1, 1);

        labelLow = new QLabel(PlotsDrawer);
        labelLow->setObjectName("labelLow");
        sizePolicy3.setHeightForWidth(labelLow->sizePolicy().hasHeightForWidth());
        labelLow->setSizePolicy(sizePolicy3);

        labelsLayout->addWidget(labelLow, 0, 2, 1, 1);

        labelHorizontalVolume = new QLabel(PlotsDrawer);
        labelHorizontalVolume->setObjectName("labelHorizontalVolume");
        sizePolicy3.setHeightForWidth(labelHorizontalVolume->sizePolicy().hasHeightForWidth());
        labelHorizontalVolume->setSizePolicy(sizePolicy3);

        labelsLayout->addWidget(labelHorizontalVolume, 0, 6, 1, 1);


        gridPlotsLayout->addLayout(labelsLayout, 0, 0, 1, 2);


        gridLayout->addLayout(gridPlotsLayout, 0, 0, 1, 1);


        retranslateUi(PlotsDrawer);

        QMetaObject::connectSlotsByName(PlotsDrawer);
    } // setupUi

    void retranslateUi(QWidget *PlotsDrawer)
    {
        PlotsDrawer->setWindowTitle(QCoreApplication::translate("PlotsDrawer", "Form", nullptr));
        labelChange->setText(QCoreApplication::translate("PlotsDrawer", "labelChange", nullptr));
        labelHigh->setText(QCoreApplication::translate("PlotsDrawer", "labelHigh", nullptr));
        labelVerticalVolume->setText(QCoreApplication::translate("PlotsDrawer", "labelVerticalVolume", nullptr));
        labelOpen->setText(QCoreApplication::translate("PlotsDrawer", "labelOpen", nullptr));
        labelClose->setText(QCoreApplication::translate("PlotsDrawer", "labelClose", nullptr));
        labelLow->setText(QCoreApplication::translate("PlotsDrawer", "labelLow", nullptr));
        labelHorizontalVolume->setText(QCoreApplication::translate("PlotsDrawer", "labelHorizontalVolume", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PlotsDrawer: public Ui_PlotsDrawer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOTSDRAWER_H
