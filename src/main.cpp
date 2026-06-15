#include "client.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Client w;
    w.resize(1600, 1200);
    w.show();
    return a.exec();
}
