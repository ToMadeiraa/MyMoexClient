#include "client.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Client w;
    w.connectToServer("127.0.0.1", quint16(6666));
    w.show();
    return a.exec();
}
