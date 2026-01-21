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
#include <QtWidgets/QCheckBox>
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
    QCheckBox *checkBoxAutorescale;
    QComboBox *comboBox;
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
        checkBoxAutorescale = new QCheckBox(centralwidget);
        checkBoxAutorescale->setObjectName(QString::fromUtf8("checkBoxAutorescale"));
        checkBoxAutorescale->setChecked(true);

        gridLayout->addWidget(checkBoxAutorescale, 0, 1, 1, 1);

        comboBox = new QComboBox(centralwidget);
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout->addWidget(comboBox, 0, 0, 1, 1);

        PlotWidget = new QCustomPlot(centralwidget);
        PlotWidget->setObjectName(QString::fromUtf8("PlotWidget"));

        gridLayout->addWidget(PlotWidget, 1, 0, 1, 2);

        Client->setCentralWidget(centralwidget);

        retranslateUi(Client);

        QMetaObject::connectSlotsByName(Client);
    } // setupUi

    void retranslateUi(QMainWindow *Client)
    {
        Client->setWindowTitle(QCoreApplication::translate("Client", "Client", nullptr));
        checkBoxAutorescale->setText(QCoreApplication::translate("Client", "Autorescale", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("Client", "GAZP", nullptr));

    } // retranslateUi

};

namespace Ui {
    class Client: public Ui_Client {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
