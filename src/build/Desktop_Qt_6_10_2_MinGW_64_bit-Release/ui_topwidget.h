/********************************************************************************
** Form generated from reading UI file 'topwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOPWIDGET_H
#define UI_TOPWIDGET_H

#include <GuiElements/mycomboboxbinsize.h>
#include <GuiElements/mycomboboxsecurity.h>
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
    MyComboBoxSecurity *comboBoxSecurities;
    MyComboBoxBinSize *comboBoxBinSize;
    QComboBox *comboBoxIndicators;

    void setupUi(QWidget *TopWidget)
    {
        if (TopWidget->objectName().isEmpty())
            TopWidget->setObjectName("TopWidget");
        TopWidget->resize(400, 42);
        TopWidget->setMaximumSize(QSize(16777215, 42));
        horizontalLayout = new QHBoxLayout(TopWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        comboBoxSecurities = new MyComboBoxSecurity(TopWidget);
        comboBoxSecurities->setObjectName("comboBoxSecurities");

        horizontalLayout->addWidget(comboBoxSecurities);

        comboBoxBinSize = new MyComboBoxBinSize(TopWidget);
        comboBoxBinSize->setObjectName("comboBoxBinSize");

        horizontalLayout->addWidget(comboBoxBinSize);

        comboBoxIndicators = new QComboBox(TopWidget);
        comboBoxIndicators->setObjectName("comboBoxIndicators");

        horizontalLayout->addWidget(comboBoxIndicators);


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
