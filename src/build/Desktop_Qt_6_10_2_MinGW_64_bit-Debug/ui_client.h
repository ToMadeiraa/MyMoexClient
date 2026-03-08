/********************************************************************************
** Form generated from reading UI file 'client.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_H
#define UI_CLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include "leftwidget.h"
#include "qcustomplot.h"
#include "topwidget.h"

QT_BEGIN_NAMESPACE

class Ui_Client
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QCustomPlot *PlotWidget;
    LeftWidget *widget;
    QComboBox *comboBox_currentSec;
    QComboBox *comboBox_binSize;
    TopWidget *widget_2;

    void setupUi(QMainWindow *Client)
    {
        if (Client->objectName().isEmpty())
            Client->setObjectName("Client");
        Client->resize(1038, 693);
        Client->setBaseSize(QSize(0, 0));
        centralwidget = new QWidget(Client);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        PlotWidget = new QCustomPlot(centralwidget);
        PlotWidget->setObjectName("PlotWidget");

        gridLayout->addWidget(PlotWidget, 2, 1, 1, 4);

        widget = new LeftWidget(centralwidget);
        widget->setObjectName("widget");

        gridLayout->addWidget(widget, 2, 0, 1, 1);

        comboBox_currentSec = new QComboBox(centralwidget);
        comboBox_currentSec->setObjectName("comboBox_currentSec");

        gridLayout->addWidget(comboBox_currentSec, 0, 0, 1, 3);

        comboBox_binSize = new QComboBox(centralwidget);
        comboBox_binSize->setObjectName("comboBox_binSize");

        gridLayout->addWidget(comboBox_binSize, 0, 3, 1, 2);

        widget_2 = new TopWidget(centralwidget);
        widget_2->setObjectName("widget_2");

        gridLayout->addWidget(widget_2, 1, 0, 1, 5);

        Client->setCentralWidget(centralwidget);

        retranslateUi(Client);

        QMetaObject::connectSlotsByName(Client);
    } // setupUi

    void retranslateUi(QMainWindow *Client)
    {
        Client->setWindowTitle(QCoreApplication::translate("Client", "Client", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Client: public Ui_Client {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
