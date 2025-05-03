#include "client.h"

Client::Client(QWidget *parent) : QWidget(parent)
{

    socket = new QTcpSocket(this);

    connect(socket, &QTcpSocket::readyRead, this, &Client::readyRead);
    connect(socket, &QTcpSocket::connected, this, &Client::connected);
    connect(socket, &QTcpSocket::disconnected, this, &Client::disconnected);

    //заполняем таблицу secid/ushort, чтобы было дешевле отправлять по сети
    SecID_Numbers["AFLT"] = 1;

    db = QSqlDatabase::addDatabase("QSQLITE");
    QString homeDir = QDir::homePath();
    homeDir.append("/MyClient/MyMoexClient/MyDatabase/moex_client.db");
    db.setDatabaseName(homeDir);


    if (!db.open()) {
        qDebug() << "Ошибка подключения к базе данных:" << db.lastError().text();
    } else {
        qDebug() << "ПОДКЛЮЧЕНО";
    }

    requestQuery = new QSqlQuery(db);
    //создали таблицу, если не существует
    requestQuery->exec("CREATE TABLE IF NOT EXISTS moex_client ( TRADENO BIGINT UNIQUE, SECID SMALLINT, PRICE FLOAT, QUANTITY INTEGER, SYSTIME DATETIME, BUYSELL BOOLEAN );");
    requestQuery->first();

    //получили последние номера сделки
    for (auto i = SecID_Numbers.cbegin(), end = SecID_Numbers.cend(); i != end; i++){
        QString req = "SELECT MAX(TRADENO) FROM moex WHERE SECID = " + QString::number(i.value());
        requestQuery->exec(req);
        requestQuery->first();
        LastTRADENOs[i.key()] = requestQuery->value(0).toLongLong();
        qDebug() << "LAST TRADENO = " << LastTRADENOs[i.key()];
    }
}

void Client::connectToServer(const QString &host, quint16 port)
{
    socket->connectToHost(host, port);
    //sendLastTradeno();
}

void Client::sendLastTradeno()
{
    QByteArray ba;
    QDataStream ds(&ba, QIODevice::WriteOnly);
    for (auto i = LastTRADENOs.cbegin(), end = LastTRADENOs.cend(); i != end; i++) {
        ushort key_ushort = SecID_Numbers[i.key()];
        long long int LastTradeno_tmp = LastTRADENOs[i.key()];

        LastTradeno_tmp = LastTradeno_tmp << 10; //сдвигаем на 10 бит влево
        LastTradeno_tmp = LastTradeno_tmp | key_ushort;

        ds << LastTradeno_tmp;
    }
    qDebug() << ba.toHex();

    if (socket->state() == QTcpSocket::ConnectedState) {
        socket->write(ba);
    }
}





void Client::readyRead()
{

    QByteArray data = socket->readAll();
    QDataStream ds(&data, QIODevice::ReadOnly);

    ushort secid_tmp = 0;
    long long int tradeno_tmp = 0;
    float price_tmp = 0;
    int quantity_tmp = 0;
    QDateTime dt_now;
    ushort buysell_tmp;

    QDateTime dt_2000; dt_2000.setDate(QDate(2000,1,1)); dt_2000.setTime(QTime(0,0,0));
    uint secondsFrom2000;

    while (!ds.atEnd()) {
        ds >> tradeno_tmp;
        buysell_tmp = tradeno_tmp & 0b1; tradeno_tmp = (tradeno_tmp >> 1);
        secid_tmp = tradeno_tmp & 0b1111111111; tradeno_tmp = (tradeno_tmp >> 10);

        ds >> price_tmp;
        ds >> quantity_tmp;

        ds >> secondsFrom2000;
        dt_now = dt_2000.addSecs(secondsFrom2000);

        qDebug() << tradeno_tmp;
        qDebug() << secid_tmp;
        qDebug() << price_tmp;
        qDebug() << quantity_tmp;
        qDebug() << dt_now;
        qDebug() << buysell_tmp;
    }
}








void Client::connected()
{
    qDebug() << "Connected to server";
    sendLastTradeno();
}

void Client::disconnected()
{
    qDebug() << "Disconnected from server";
}


