#ifndef MYCOMBOBOXSECURITY_H
#define MYCOMBOBOXSECURITY_H

#include <QObject>
#include <QComboBox>
#include <QMap>

class MyComboBoxSecurity  : public QComboBox
{
    Q_OBJECT
public:
    MyComboBoxSecurity(QWidget *parent = 0);

    void fillComboBox(QMap<QString, ushort> securities);
private:
};

#endif // MYCOMBOBOXSECURITY_H
