#ifndef MYCOMBOBOXBINSIZE_H
#define MYCOMBOBOXBINSIZE_H

#include <QObject>
#include <QComboBox>

class MyComboBoxBinSize  : public QComboBox
{
    Q_OBJECT
public:
    MyComboBoxBinSize(QWidget *parent = 0);

private:
    void fillComboBox();

public slots:
    void itemChanged_slot();

signals:
    void binSizeChanged_signal(uint);
};

#endif // MYCOMBOBOXBINSIZE_H
