#ifndef BINCOMBOBOX_H
#define BINCOMBOBOX_H

#include <QObject>
#include <QComboBox>

class BinComboBox : public QWidget
{
    Q_OBJECT
public:
    BinComboBox(QComboBox *cb);
    QComboBox* cb;

private:
    void fillComboBox();

public slots:
    void cbItemChanged_slot();

signals:
    void changedBinSize_signal(uint);

};

#endif // BINCOMBOBOX_H
