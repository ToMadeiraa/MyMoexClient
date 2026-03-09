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

    //подключились к БД
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setPort(5432);
    db.setDatabaseName("db_client");
    db.setUserName("postgres");
    db.setPassword("12345678");

    if (!db.open()) {
        qDebug() << "Ошибка подключения к базе данных:" << db.lastError().text();
    } else {
        qDebug() << "ПОДКЛЮЧЕНО";
    }

    requestQuery = new QSqlQuery(db);

    //data update
    sqlUpdater = new SqlUpdater;
    sqlUpdater->requestQuery = this->requestQuery;
    sqlUpdater->mtx = &this->mtx;
    sqlUpdaterThread = new QThread(this);
    sqlUpdater->moveToThread(sqlUpdaterThread);

    sqlUpdaterThread->start();

    //data for drawing
    sqlSelector = new SqlSelector;
    sqlSelector->requestQuery = this->requestQuery;
    sqlSelector->priceData = &this->priceData;
    sqlSelector->timeData = &this->timeData;
    sqlSelector->quantityData = &this->quantityData;
    sqlSelector->buysellData = &this->buysellData;
    sqlSelector->mtx = &this->mtx;
    sqlSelectorThread = new QThread(this);
    sqlSelector->moveToThread(sqlSelectorThread);

    sqlSelectorThread->start();

    //drawer
    plotDrawer = new PlotDrawer(ui->PlotWidget);
    plotDrawer->priceData = &this->priceData;
    plotDrawer->timeData = &this->timeData;
    plotDrawer->quantityData = &this->quantityData;
    plotDrawer->buysellData = &this->buysellData;
    plotDrawer->autoRescale = true;

    //ui
    getTopWidget()->getComboBoxSecurities()->fillComboBox(sqlUpdater->SecID_Numbers);
    connectSlots();
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

void Client::connectSlots()
{
    connect(sqlSelectorThread, &QThread::finished, sqlSelectorThread, &QThread::deleteLater);
    connect(sqlUpdaterThread, &QThread::started, sqlUpdater, &SqlUpdater::process);
    connect(sqlUpdater, &SqlUpdater::finished, sqlUpdaterThread, &QThread::quit);
    connect(sqlUpdater, &SqlUpdater::finished, sqlUpdater, &SqlUpdater::deleteLater);
    connect(sqlUpdaterThread, &QThread::finished, sqlUpdaterThread, &QThread::deleteLater);

    connect(getTopWidget()->getComboBoxBinSize(), SIGNAL(binSizeChanged_signal(uint)), plotDrawer, SLOT(redrawPlotByBinSizeChange_slot(uint)));
    connect(getTopWidget()->getComboBoxSecurities(), SIGNAL(currentIndexChanged(int)), this, SLOT(redrawPlotBySecurityChange_slot()));

    connect(ui->PlotWidget, SIGNAL(mouseWheel(QWheelEvent*)), plotDrawer, SLOT(setNewRange(QWheelEvent*)));
    connect(ui->PlotWidget->xAxis, SIGNAL(selectionChanged(const QCPAxis::SelectableParts&)), plotDrawer, SLOT(setNewRangeX()));
    connect(ui->PlotWidget->yAxis2, SIGNAL(selectionChanged(const QCPAxis::SelectableParts&)), plotDrawer, SLOT(setNewRangeY()));
    connect(ui->PlotWidget, SIGNAL(mouseMove(QMouseEvent *)), plotDrawer, SLOT(mouseMoved(QMouseEvent*)));

    connect(ui->PlotWidget->yAxis2, SIGNAL(rangeChanged(QCPRange)), ui->PlotWidget->yAxis, SLOT(setRange(QCPRange))); // left axis only mirrors inner right axis
}

TopWidget *Client::getTopWidget()
{
    return ui->topWidget;
}

LeftWidget *Client::getLeftWidget()
{
    return ui->leftWidget;
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

void Client::redrawPlotBySecurityChange_slot()
{
    QString currentSec = getTopWidget()->getComboBoxSecurities()->currentText().toLower() + "_client";

    plotDrawer->timeData->clear();
    plotDrawer->priceData->clear();
    plotDrawer->quantityData->clear();
    plotDrawer->buysellData->clear();
    plotDrawer->candlesticks->data().clear();

    sqlSelector->selectData(currentSec);
    plotDrawer->collectCandleInfo();

    plotDrawer->candlesticks->setData(plotDrawer->time,
                                      plotDrawer->open,
                                      plotDrawer->high,
                                      plotDrawer->low,
                                      plotDrawer->close);
    plotDrawer->volumeBars->setData(plotDrawer->time,
                                    plotDrawer->volume);


    plotDrawer->drawPlot();
}

//void Client::setAutorescale()
//{
//    if (ui->checkBoxAutorescale->isChecked())
//    {
//        plotDrawer->autoRescale = true;
//    }
//    else
//    {
//        plotDrawer->autoRescale = false;
//    }
//}
