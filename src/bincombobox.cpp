#include "bincombobox.h"

BinComboBox::BinComboBox(QComboBox *cb)
{
    this->cb = cb;
    fillComboBox();
    connect(this->cb, SIGNAL(currentIndexChanged(int)), this, SLOT(cbItemChanged_slot()));
}

void BinComboBox::fillComboBox()
{
    cb->addItem("1 minute");
    cb->addItem("5 minutes");
    cb->addItem("10 minutes");
    cb->addItem("15 minutes");
    cb->addItem("30 minutes");

    cb->addItem("1 hour");
    cb->addItem("2 hours");
    cb->addItem("4 hours");
    cb->addItem("12 hours");

    cb->addItem("1 day");
    cb->addItem("1 week");
    cb->addItem("1 month");
}

void BinComboBox::cbItemChanged_slot()
{
    uint currentItemIndex = cb->currentIndex();
    if (currentItemIndex == 0)
        emit changedBinSize_signal(60);
    else if (currentItemIndex == 1)
        emit changedBinSize_signal(300);
    else if (currentItemIndex == 2)
        emit changedBinSize_signal(600);
    else if (currentItemIndex == 3)
        emit changedBinSize_signal(900);
    else if (currentItemIndex == 4)
        emit changedBinSize_signal(1800);
    else if (currentItemIndex == 5)
        emit changedBinSize_signal(3600);
    else if (currentItemIndex == 6)
        emit changedBinSize_signal(7200);
    else if (currentItemIndex == 7)
        emit changedBinSize_signal(14400);
    else if (currentItemIndex == 8)
        emit changedBinSize_signal(43200);
    else if (currentItemIndex == 9)
        emit changedBinSize_signal(86400);
    else if (currentItemIndex == 10)
        emit changedBinSize_signal(604800);
    else if (currentItemIndex == 11)
        emit changedBinSize_signal(2592000);

}
