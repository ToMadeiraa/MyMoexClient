#include "SqlUpdater.h"

SqlUpdater::SqlUpdater()
{
    socket = new QTcpSocket(this);

    connect(socket, &QTcpSocket::connected, this, &SqlUpdater::connected);
    connect(socket, &QTcpSocket::readyRead, this, &SqlUpdater::readyRead);
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
    ds.setByteOrder(QDataStream::BigEndian);
    ds.setFloatingPointPrecision(QDataStream::SinglePrecision);

    for (const auto &key : LastTRADENOs.keys())
    {
        ushort key_ushort = SecID_Numbers[key];
        long long int LastTradeno_tmp = LastTRADENOs[key];

        LastTradeno_tmp = LastTradeno_tmp << 10; //сдвигаем на 10 бит влево
        LastTradeno_tmp = LastTradeno_tmp | key_ushort;

        ds << LastTradeno_tmp;
    }

    if (socket->state() == QTcpSocket::ConnectedState) {
        socket->write(ba);
    }
}

void SqlUpdater::process()
{
    mtx->lock();

    //заполняем таблицу secid/ushort, чтобы было дешевле отправлять по сети
    SecID_Numbers["GAZP"]   = 1;
    SecID_Numbers["SBER"]   = 2;
    SecID_Numbers["LKOH"]   = 3;
    SecID_Numbers["T"]      = 4;
    SecID_Numbers["PLZL"]   = 5;
    SecID_Numbers["RUAL"]   = 6;
    SecID_Numbers["MGNT"]   = 7;
    SecID_Numbers["NVTK"]   = 8;
    SecID_Numbers["GMKN"]   = 9;
    SecID_Numbers["VTBR"]   = 10;
    SecID_Numbers["AFLT"]   = 11;
    SecID_Numbers["MOEX"]   = 12;
    SecID_Numbers["NLMK"]   = 13;
    SecID_Numbers["TRNFP"]  = 14;
    SecID_Numbers["SELG"]   = 15;
    SecID_Numbers["SMLT"]   = 16;
    SecID_Numbers["SNGSP"]  = 17;
    SecID_Numbers["ROSN"]   = 18;
    SecID_Numbers["MTSS"]   = 19;
    SecID_Numbers["AFKS"]   = 20;
    SecID_Numbers["VKCO"]   = 21;
    SecID_Numbers["EUTR"]   = 22;
    SecID_Numbers["CHMF"]   = 23;
    SecID_Numbers["ELMT"]   = 24;
    SecID_Numbers["ALRS"]   = 25;
    SecID_Numbers["IRKT"]   = 26;
    SecID_Numbers["POSI"]   = 27;
    SecID_Numbers["UNAC"]   = 28;
    SecID_Numbers["RAGR"]   = 29;
    SecID_Numbers["MBNK"]   = 30;
    SecID_Numbers["SGZH"]   = 31;
    SecID_Numbers["KMAZ"]   = 32;
    SecID_Numbers["MVID"]   = 33;
    SecID_Numbers["TRMK"]   = 34;
    SecID_Numbers["RNFT"]   = 35;
    SecID_Numbers["FLOT"]   = 36;
    SecID_Numbers["YDEX"]   = 37;
    SecID_Numbers["ASTR"]   = 38;

    //создали таблицу, если не существует
    for (const auto &key : SecID_Numbers.keys())
    {
        QString companyName = QString(key) + QString("_client");
        qDebug() << "Creating " << companyName;
        requestQuery->exec("CREATE TABLE IF NOT EXISTS " + companyName + " ( TRADENO BIGINT UNIQUE, PRICE FLOAT, QUANTITY INTEGER, SYSTIME TIMESTAMP, BUYSELL SMALLINT );");
        requestQuery->first();
    }

    for (const auto &key : SecID_Numbers.keys())
    {
        QString companyName = QString(key) + QString("_client");
        QString req = "SELECT MAX(TRADENO) FROM " + companyName;
        requestQuery->exec(req);
        requestQuery->first();
        LastTRADENOs[key] = requestQuery->value(0).toLongLong();
    }

    connectToServer("127.0.0.1", quint16(6666));

    mtx->unlock();
}

void SqlUpdater::readyRead()
{
    qDebug() << "GOT MSG ";
    if (sizeOfCompanyPack == -1)
    {
        socket->read((char*)&sizeOfCompanyPack, 4);
        qDebug() << "sizeOfCompanyPack = " << sizeOfCompanyPack;
    }
    QByteArray data;
    //ждем оставшуюся часть пакета
    if (sizeOfCompanyPack > socket->bytesAvailable())
    {
        return;
    }
    else
    {
        //socket->read(&data, sizeOfCompanyPack);
        data = socket->read(sizeOfCompanyPack);
        qDebug() << "data.size() == " << data.size();
        sizeOfCompanyPack = -1;
    }

    QDataStream ds(&data, QIODevice::ReadOnly);
    ds.setByteOrder(QDataStream::BigEndian);
    ds.setFloatingPointPrecision(QDataStream::SinglePrecision);

    ushort secid_tmp = 0;
    long long int tradeno_tmp = 0;
    float price_tmp = 0;
    int quantity_tmp = 0;
    long long int systime_tmp;
    bool buysell_tmp;

    uint secondsFrom2000;

    QString bigInsertString = "INSERT INTO ";
    bool flagString = false;
    while (!ds.atEnd()) {
        ds >> tradeno_tmp;
        buysell_tmp = tradeno_tmp & 0b1; tradeno_tmp = (tradeno_tmp >> 1);

        if (flagString == false)
        {
            secid_tmp = tradeno_tmp & 0b1111111111;
            QString companyName;
            for (const auto &key : SecID_Numbers.keys())
            {
                if (SecID_Numbers[key] == secid_tmp)
                {
                    companyName = QString(key) + QString("_client");
                    break;
                }
            }
            bigInsertString+=companyName;
            bigInsertString+=QString(" (TRADENO, PRICE, QUANTITY, SYSTIME, BUYSELL) VALUES ");

            flagString = true;
        }

        tradeno_tmp = (tradeno_tmp >> 10);

        ds >> price_tmp;
        ds >> quantity_tmp;

        ds >> secondsFrom2000;
        systime_tmp = secondsFrom2000 + secsBefore2000;
        QString isoString = QDateTime::fromSecsSinceEpoch(systime_tmp).toString(Qt::ISODate);

        QChar buysell_char = buysell_tmp == 1 ? '1' : '0';

        QString valuesInsertString = "(";
        valuesInsertString.append(QString::number(tradeno_tmp)); valuesInsertString.append(", ");
        valuesInsertString.append(QString::number(price_tmp)); valuesInsertString.append(", ");
        valuesInsertString.append(QString::number(quantity_tmp)); valuesInsertString.append(", '");
        valuesInsertString.append(isoString); valuesInsertString.append("', ");
        valuesInsertString.append(buysell_char); valuesInsertString.append("),");
        bigInsertString.append(valuesInsertString);
    }
    bigInsertString.chop(1);
    bigInsertString.append(";");

    mtx->lock();

    //qDebug() << bigInsertString;
    //qDebug() << "===========================================";
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
