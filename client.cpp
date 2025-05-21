#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Client)
{
    ui->setupUi(this);
    readConfigFile();

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

    // requestQueryUpdater = new QSqlQuery(db);
    // requestQuerySelector = new QSqlQuery(db);
    requestQuery = new QSqlQuery(db);

    ///////////////
    sqlUpdater = new SqlUpdater;
    //sqlUpdater->db = this->db;
    sqlUpdater->requestQuery = this->requestQuery;
    sqlUpdater->mtx = &this->mtx;
    sqlUpdaterThread = new QThread(this);
    sqlUpdater->moveToThread(sqlUpdaterThread);

    connect(sqlUpdaterThread, &QThread::started, sqlUpdater, &SqlUpdater::process);
    connect(sqlUpdater, &SqlUpdater::finished, sqlUpdaterThread, &QThread::quit);
    connect(sqlUpdater, &SqlUpdater::finished, sqlUpdater, &SqlUpdater::deleteLater);
    connect(sqlUpdaterThread, &QThread::finished, sqlUpdaterThread, &QThread::deleteLater);

    sqlUpdaterThread->start();

    ///////////////
    sqlSelector = new SqlSelector;
    //sqlSelector->db = this->db;
    sqlSelector->requestQuery = this->requestQuery;
    sqlSelector->priceData = &this->priceData;
    sqlSelector->timeData = &this->timeData;
    sqlSelector->mtx = &this->mtx;
    sqlSelectorThread = new QThread(this);
    sqlSelector->moveToThread(sqlSelectorThread);

    connect(sqlSelectorThread, &QThread::finished, sqlSelectorThread, &QThread::deleteLater);

    sqlSelectorThread->start();


    ///////////////
    plotDrawer = new PlotDrawer(ui->PlotWidget);
    plotDrawer->priceData = &this->priceData;
    plotDrawer->timeData = &this->timeData;

    timerDraw = new QTimer;
    connect(timerDraw, SIGNAL(timeout()), plotDrawer, SLOT(drawPlot()));
    timerDraw->start(100);
    plotDrawer->drawPlot();

    connect(ui->checkBoxAutorescale, SIGNAL(stateChanged(int)), this, SLOT(setAutorescale()));
    connect(ui->PlotWidget, SIGNAL(mouseWheel(QWheelEvent*)), plotDrawer, SLOT(setNewRange(QWheelEvent*)));
    connect(ui->PlotWidget->xAxis, SIGNAL(selectionChanged(const QCPAxis::SelectableParts&)), plotDrawer, SLOT(setNewRangeX()));
    connect(ui->PlotWidget->yAxis2, SIGNAL(selectionChanged(const QCPAxis::SelectableParts&)), plotDrawer, SLOT(setNewRangeY()));
    connect(ui->PlotWidget, SIGNAL(mouseMove(QMouseEvent *)), plotDrawer, SLOT(mouseMoved(QMouseEvent*)));

    connect(ui->PlotWidget->yAxis2, SIGNAL(rangeChanged(QCPRange)), ui->PlotWidget->yAxis, SLOT(setRange(QCPRange))); // left axis only mirrors inner right axis
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

void Client::setAutorescale()
{
    if (ui->checkBoxAutorescale->isChecked()) plotDrawer->autoRescale = true;
    else plotDrawer->autoRescale = false;
}

