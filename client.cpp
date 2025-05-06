#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Client)
{

    //проверка обновления
    socketUpdate = new QTcpSocket();

    connect(socketUpdate, &QTcpSocket::connected, this, &Client::connected);
    connect(socketUpdate, &QTcpSocket::readyRead, this, &Client::readyRead);
    connect(socketUpdate, &QTcpSocket::disconnected, this, &Client::disconnected);

    if (checkNewVersion()) {
        qDebug() << "Есть новая версия";
        update();
    } else {
        qDebug() << "Обновление не требуется";
    }

    //подключение к БД
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString homeDir = QDir::homePath();
    homeDir.append("/MyClient/MyMoexClient/MyDatabase/moex_client.db");
    db.setDatabaseName(homeDir);

    if (!db.open()) {
        qDebug() << "Ошибка подключения к базе данных: " << db.lastError().text();
        return;
    } else {
        qDebug() << "Успешное подключение к базе данных";
    }

    requestQuery = new QSqlQuery(db);

    sqlUpdater = new SqlUpdater;
    sqlUpdater->db = this->db;
    sqlUpdater->requestQuery = this->requestQuery;

    sqlUpdaterThread = new QThread(this);

    sqlUpdater->moveToThread(sqlUpdaterThread);

    connect(sqlUpdaterThread, &QThread::started, sqlUpdater, &SqlUpdater::process);
    connect(sqlUpdater, &SqlUpdater::finished, sqlUpdaterThread, &QThread::quit);
    connect(sqlUpdater, &SqlUpdater::finished, sqlUpdater, &SqlUpdater::deleteLater);
    connect(sqlUpdaterThread, &QThread::finished, sqlUpdaterThread, &QThread::deleteLater);

    sqlUpdaterThread->start();

    readConfigFile();
    ui->setupUi(this);
}

Client::~Client()
{
    delete ui;
}


void Client::readConfigFile()
{
    QString fileDir = QDir::homePath();
    fileDir.append("/MyClient/MyMoexClient/config.xml");

    QFile file(fileDir);
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    QXmlStreamReader xml(file.readAll());
    while (!xml.atEnd() && !xml.hasError()) {
        xml.readNext();

        if (xml.name().toString() == "row") {

            ver.Major = xml.attributes().at(0).value().toUInt();
            ver.Minor = xml.attributes().at(1).value().toUInt();
            ver.Maintenance = xml.attributes().at(2).value().toUInt();

            break;
        }
    }

    file.close();
}

bool Client::checkNewVersion()
{

    socketUpdate->connectToHost("127.0.0.1", quint16(6667));
    return true;
}

void Client::update()
{
    ;
}

void Client::readyRead()
{
    qDebug() << "NEW MESSAGE!";
    QByteArray versionData = socketUpdate->readAll();
    QDataStream ds(&versionData, QIODevice::ReadOnly);

    ds >> ver.Major;
    ds >> ver.Minor;
    ds >> ver.Maintenance;

    ver.print();
}

void Client::connected()
{
    qDebug() << "Connected to update server";
}

void Client::disconnected()
{
    qDebug() << "Disconnected from update server";
}
