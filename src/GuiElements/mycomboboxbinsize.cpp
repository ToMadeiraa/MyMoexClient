#include "mycomboboxbinsize.h"

MyComboBoxBinSize::MyComboBoxBinSize(QWidget *parent) :
    QComboBox(parent)
{
    fillComboBox();

    connect(this, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MyComboBoxBinSize::itemChanged_slot);
}

void MyComboBoxBinSize::fillComboBox()
{
    addItem("1 minute");
    addItem("5 minutes");
    addItem("10 minutes");
    addItem("15 minutes");
    addItem("30 minutes");

    addItem("1 hour");
    addItem("2 hours");
    addItem("4 hours");
    addItem("12 hours");

    addItem("1 day");
    addItem("1 week");
    addItem("1 month");
}

void MyComboBoxBinSize::itemChanged_slot()
{
    uint currentItemIndex = currentIndex();
    if (currentItemIndex == 0)
        emit binSizeChanged_signal(60);
    else if (currentItemIndex == 1)
        emit binSizeChanged_signal(300);
    else if (currentItemIndex == 2)
        emit binSizeChanged_signal(600);
    else if (currentItemIndex == 3)
        emit binSizeChanged_signal(900);
    else if (currentItemIndex == 4)
        emit binSizeChanged_signal(1800);
    else if (currentItemIndex == 5)
        emit binSizeChanged_signal(3600);
    else if (currentItemIndex == 6)
        emit binSizeChanged_signal(7200);
    else if (currentItemIndex == 7)
        emit binSizeChanged_signal(14400);
    else if (currentItemIndex == 8)
        emit binSizeChanged_signal(43200);
    else if (currentItemIndex == 9)
        emit binSizeChanged_signal(86400);
    else if (currentItemIndex == 10)
        emit binSizeChanged_signal(604800);
    else if (currentItemIndex == 11)
        emit binSizeChanged_signal(2592000);
}
