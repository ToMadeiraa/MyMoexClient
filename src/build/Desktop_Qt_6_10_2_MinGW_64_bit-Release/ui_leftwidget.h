/********************************************************************************
** Form generated from reading UI file 'leftwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LEFTWIDGET_H
#define UI_LEFTWIDGET_H

#include <GuiElements/mypushbutton.h>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LeftWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    MyPushButton *pushButton;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *LeftWidget)
    {
        if (LeftWidget->objectName().isEmpty())
            LeftWidget->setObjectName("LeftWidget");
        LeftWidget->resize(40, 308);
        LeftWidget->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout_2 = new QVBoxLayout(LeftWidget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton = new MyPushButton(LeftWidget);
        pushButton->setObjectName("pushButton");
        pushButton->setMinimumSize(QSize(40, 40));
        pushButton->setMaximumSize(QSize(40, 40));

        verticalLayout_2->addWidget(pushButton);

        verticalSpacer = new QSpacerItem(40, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        retranslateUi(LeftWidget);

        QMetaObject::connectSlotsByName(LeftWidget);
    } // setupUi

    void retranslateUi(QWidget *LeftWidget)
    {
        LeftWidget->setWindowTitle(QCoreApplication::translate("LeftWidget", "Form", nullptr));
        pushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LeftWidget: public Ui_LeftWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEFTWIDGET_H
