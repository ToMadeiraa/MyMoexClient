#ifndef LEFTWIDGET_H
#define LEFTWIDGET_H

#include <QWidget>
#include <QPushButton>


namespace Ui {
class LeftWidget;
}

class LeftWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LeftWidget(QWidget *parent = nullptr);
    ~LeftWidget();



private:
    Ui::LeftWidget *ui;
};

#endif // LEFTWIDGET_H
