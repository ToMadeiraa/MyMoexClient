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
#include <QtWidgets/QSpacerItem>
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
    QGridLayout *gridLayout_5;
    PlotsDrawer *PlotsWidget;
    LeftWidget *leftWidget;
    TopWidget *topWidget;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;

    void setupUi(QMainWindow *Client)
    {
        if (Client->objectName().isEmpty())
            Client->setObjectName("Client");
        Client->resize(1409, 709);
        Client->setBaseSize(QSize(0, 0));
        centralwidget = new QWidget(Client);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName("gridLayout_5");
        PlotsWidget = new PlotsDrawer(centralwidget);
        PlotsWidget->setObjectName("PlotsWidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PlotsWidget->sizePolicy().hasHeightForWidth());
        PlotsWidget->setSizePolicy(sizePolicy);
        PlotsWidget->setMinimumSize(QSize(800, 600));

        gridLayout_5->addWidget(PlotsWidget, 2, 1, 1, 1);

        leftWidget = new LeftWidget(centralwidget);
        leftWidget->setObjectName("leftWidget");
        leftWidget->setMaximumSize(QSize(40, 16777215));

        gridLayout_5->addWidget(leftWidget, 2, 0, 1, 1);

        topWidget = new TopWidget(centralwidget);
        topWidget->setObjectName("topWidget");
        topWidget->setMaximumSize(QSize(16777215, 40));

        gridLayout_5->addWidget(topWidget, 0, 0, 1, 2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_5->addItem(horizontalSpacer, 2, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_5->addItem(verticalSpacer, 3, 1, 1, 1);


        gridLayout->addLayout(gridLayout_5, 2, 2, 1, 1);

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
