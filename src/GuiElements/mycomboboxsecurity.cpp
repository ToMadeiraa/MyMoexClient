#include "mycomboboxsecurity.h"

MyComboBoxSecurity::MyComboBoxSecurity(QWidget *parent) :
    QComboBox(parent)
{
}

void MyComboBoxSecurity::fillComboBox(QMap<QString, ushort> securities)
{
    //add later
    // QString path = "/home/osboxes/Downloads/PetProject/MyMoexClient/src/gazp.png";
    // QIcon ic(path);
    for (const auto &k : securities.keys())
    {
        addItem(k);
    }
}
