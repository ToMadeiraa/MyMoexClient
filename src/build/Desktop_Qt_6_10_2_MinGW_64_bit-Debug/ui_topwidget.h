/********************************************************************************
** Form generated from reading UI file 'topwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOPWIDGET_H
#define UI_TOPWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TopWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox;
    QComboBox *comboBox_2;
    QComboBox *comboBox_3;

    void setupUi(QWidget *TopWidget)
    {
        if (TopWidget->objectName().isEmpty())
            TopWidget->setObjectName("TopWidget");
        TopWidget->resize(400, 42);
        TopWidget->setMaximumSize(QSize(16777215, 42));
        horizontalLayout = new QHBoxLayout(TopWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        comboBox = new QComboBox(TopWidget);
        comboBox->setObjectName("comboBox");

        horizontalLayout->addWidget(comboBox);

        comboBox_2 = new QComboBox(TopWidget);
        comboBox_2->setObjectName("comboBox_2");

        horizontalLayout->addWidget(comboBox_2);

        comboBox_3 = new QComboBox(TopWidget);
        comboBox_3->setObjectName("comboBox_3");

        horizontalLayout->addWidget(comboBox_3);


        retranslateUi(TopWidget);

        QMetaObject::connectSlotsByName(TopWidget);
    } // setupUi

    void retranslateUi(QWidget *TopWidget)
    {
        TopWidget->setWindowTitle(QCoreApplication::translate("TopWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TopWidget: public Ui_TopWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOPWIDGET_H
