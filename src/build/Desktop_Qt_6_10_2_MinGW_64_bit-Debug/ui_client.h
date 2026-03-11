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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <plotsdrawer.h>
#include "leftwidget.h"
#include "topwidget.h"

QT_BEGIN_NAMESPACE

class Ui_Client
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    TopWidget *topWidget;
    LeftWidget *leftWidget;
    PlotsDrawer *PlotsWidget;

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
        topWidget = new TopWidget(centralwidget);
        topWidget->setObjectName("topWidget");
        topWidget->setMaximumSize(QSize(16777215, 40));

        gridLayout->addWidget(topWidget, 0, 0, 1, 3);

        leftWidget = new LeftWidget(centralwidget);
        leftWidget->setObjectName("leftWidget");
        leftWidget->setMaximumSize(QSize(40, 16777215));

        gridLayout->addWidget(leftWidget, 1, 0, 2, 1);

        PlotsWidget = new PlotsDrawer(centralwidget);
        PlotsWidget->setObjectName("PlotsWidget");

        gridLayout->addWidget(PlotsWidget, 1, 1, 2, 2);

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
