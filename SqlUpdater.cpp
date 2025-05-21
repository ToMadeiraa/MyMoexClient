#include "SqlUpdater.h"

SqlUpdater::SqlUpdater()
{
    socket = new QTcpSocket();

    connect(socket, &QTcpSocket::readyRead, this, &SqlUpdater::readyRead);
    connect(socket, &QTcpSocket::connected, this, &SqlUpdater::connected);
    connect(socket, &QTcpSocket::disconnected, this, &SqlUpdater::disconnected);

    secsBefore2000 = 946684800; //количество секунд, прошедших до 01.01.2000 00:00:00
}

void SqlUpdater::connectToServer(const QString &host, quint16 port)
{
    socket->connectToHost(host, port);
}

void SqlUpdater::sendLastTradeno()
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

void SqlUpdater::process()
{
    mtx->lock();

    //заполняем таблицу secid/ushort, чтобы было дешевле отправлять по сети
    SecID_Numbers["GAZP"] = 1;

    //создали таблицу, если не существует
    requestQuery->exec("CREATE TABLE IF NOT EXISTS moex_client ( TRADENO BIGINT UNIQUE, SECID SMALLINT, PRICE FLOAT, QUANTITY INTEGER, SYSTIME BIGINT, BUYSELL BOOLEAN );");
    requestQuery->first();

    for (auto i = SecID_Numbers.cbegin(), end = SecID_Numbers.cend(); i != end; i++){
        QString req = "SELECT MAX(TRADENO) FROM moex WHERE SECID = " + QString::number(i.value());
        requestQuery->exec(req);
        requestQuery->first();
        LastTRADENOs[i.key()] = requestQuery->value(0).toLongLong();
    }

    connectToServer("127.0.0.1", quint16(6666));

    mtx->unlock();
}

void SqlUpdater::readyRead()
{
    QByteArray data = socket->readAll();
    QDataStream ds(&data, QIODevice::ReadOnly);

    ushort secid_tmp = 0;
    long long int tradeno_tmp = 0;
    float price_tmp = 0;
    int quantity_tmp = 0;
    long long int systime_tmp;
    bool buysell_tmp;

    uint secondsFrom2000;

    QString bigInsertString = "INSERT INTO moex_client (TRADENO, SECID, PRICE, QUANTITY, SYSTIME, BUYSELL) VALUES ";

    while (!ds.atEnd()) {
        ds >> tradeno_tmp;
        buysell_tmp = tradeno_tmp & 0b1; tradeno_tmp = (tradeno_tmp >> 1);
        secid_tmp = tradeno_tmp & 0b1111111111; tradeno_tmp = (tradeno_tmp >> 10);

        ds >> price_tmp;
        ds >> quantity_tmp;

        ds >> secondsFrom2000;
        systime_tmp = secondsFrom2000 + secsBefore2000;

        QChar buysell_char = buysell_tmp == 1 ? '1' : '0';

        QString valuesInsertString = "(";
        valuesInsertString.append(QString::number(tradeno_tmp)); valuesInsertString.append(", ");
        valuesInsertString.append(QString::number(secid_tmp)); valuesInsertString.append(", ");
        valuesInsertString.append(QString::number(price_tmp)); valuesInsertString.append(", ");
        valuesInsertString.append(QString::number(quantity_tmp)); valuesInsertString.append(", '");
        valuesInsertString.append(QString::number(systime_tmp)); valuesInsertString.append("', ");
        valuesInsertString.append(buysell_char); valuesInsertString.append("),");
        bigInsertString.append(valuesInsertString);
    }
    bigInsertString.chop(1);
    bigInsertString.append(";");
    //qDebug() << bigInsertString <<  "      INSERTING..." << QTime::currentTime();

    mtx->lock();

    requestQuery->exec(bigInsertString);
    requestQuery->first();

    mtx->unlock();
}

void SqlUpdater::connected()
{
    qDebug() << "Connected to SQL server";
    sendLastTradeno();
}

void SqlUpdater::disconnected()
{
    qDebug() << "Disconnected from SQL server";
}
