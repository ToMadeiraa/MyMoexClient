/********************************************************************************
** Form generated from reading UI file 'client.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
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
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_Client
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QComboBox *comboBox_currentSec;
    QComboBox *comboBox_binSize;
    QCustomPlot *PlotWidget;

    void setupUi(QMainWindow *Client)
    {
        if (Client->objectName().isEmpty())
            Client->setObjectName(QString::fromUtf8("Client"));
        Client->resize(800, 600);
        Client->setBaseSize(QSize(0, 0));
        centralwidget = new QWidget(Client);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        comboBox_currentSec = new QComboBox(centralwidget);
        comboBox_currentSec->setObjectName(QString::fromUtf8("comboBox_currentSec"));

        gridLayout->addWidget(comboBox_currentSec, 0, 0, 1, 3);

        comboBox_binSize = new QComboBox(centralwidget);
        comboBox_binSize->setObjectName(QString::fromUtf8("comboBox_binSize"));

        gridLayout->addWidget(comboBox_binSize, 0, 3, 1, 1);

        PlotWidget = new QCustomPlot(centralwidget);
        PlotWidget->setObjectName(QString::fromUtf8("PlotWidget"));

        gridLayout->addWidget(PlotWidget, 1, 0, 1, 4);

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
