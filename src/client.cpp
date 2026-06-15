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

    //ui
    p_leftTopWidget = new QWidget();
    p_leftBottomWidget = new QWidget();
    p_rightWidget = new QWidget();
    plotsDrawer = new PlotsDrawer();
    p_additionalPlotDrawer = new AdditionalPlotDrawer(p_leftBottomWidget);
    p_lw = new LeftWidget();
    p_tw = new TopWidget();
    p_topLeftGridLayout = new QGridLayout(p_leftTopWidget);
    p_topLeftGridLayout->addWidget(p_tw, 0, 1);
    p_topLeftGridLayout->addWidget(p_lw, 1, 0);
    p_topLeftGridLayout->addWidget(plotsDrawer, 1, 1);

    // Создаем главный горизонтальный сплиттер
    p_mainSplitter = new QSplitter(Qt::Horizontal, this);

    // Создаем вертикальный сплиттер для левой панели
    p_leftSplitter = new QSplitter(Qt::Vertical);

    p_leftSplitter->addWidget(p_leftTopWidget);
    p_leftSplitter->addWidget(p_additionalPlotDrawer);

    p_leftSplitter->setSizes({600, 600});  // Одинаковая высота
    p_leftSplitter->setStretchFactor(0, 1);
    p_leftSplitter->setStretchFactor(1, 1);
    p_leftSplitter->setHandleWidth(2);
    p_leftSplitter->setChildrenCollapsible(false);

    p_mainSplitter->addWidget(p_leftSplitter);
    p_mainSplitter->addWidget(p_rightWidget);

    // Настройка главного горизонтального сплиттера
    p_mainSplitter->setSizes({800, 800});
    p_mainSplitter->setStretchFactor(0, 1);  // Левая панель
    p_mainSplitter->setStretchFactor(1, 2);  // Правая панель
    p_mainSplitter->setHandleWidth(2);
    p_mainSplitter->setChildrenCollapsible(false);

    // Стилизация разделителей
    p_mainSplitter->setStyleSheet(
        "QSplitter::handle {"
        "   background-color: #aaaaaa;"
        "}"
        "QSplitter::handle:hover {"
        "   background-color: #888888;"
        "}"
        );

    p_leftSplitter->setStyleSheet(
        "QSplitter::handle {"
        "   background-color: #aaaaaa;"
        "}"
        "QSplitter::handle:hover {"
        "   background-color: #888888;"
        "}"
        );

    setCentralWidget(p_mainSplitter);

    plotsDrawer->p_priceData = &this->priceData;
    plotsDrawer->p_timeData = &this->timeData;
    plotsDrawer->p_quantityData = &this->quantityData;
    plotsDrawer->p_buysellData = &this->buysellData;

    p_tw->getComboBoxSecurities()->fillComboBox(sqlUpdater->SecID_Numbers);
    connectSlots();
    redrawPlotBySecurityChange_slot();
}

Client::~Client()
{
    delete ui;
}

void Client::connectSlots()
{
    connect(sqlSelectorThread, &QThread::finished, sqlSelectorThread, &QThread::deleteLater);
    connect(sqlUpdaterThread, &QThread::started, sqlUpdater, &SqlUpdater::process);
    connect(sqlUpdater, &SqlUpdater::finished, sqlUpdaterThread, &QThread::quit);
    connect(sqlUpdater, &SqlUpdater::finished, sqlUpdater, &SqlUpdater::deleteLater);
    connect(sqlUpdaterThread, &QThread::finished, sqlUpdaterThread, &QThread::deleteLater);

    connect(p_tw->getComboBoxBinSize(), SIGNAL(binSizeChanged_signal(uint)), plotsDrawer, SLOT(redrawPlotByBinSizeChange_slot(uint)));
    connect(p_tw->getComboBoxSecurities(), SIGNAL(currentIndexChanged(int)), this, SLOT(redrawPlotBySecurityChange_slot()));
}


void Client::redrawPlotBySecurityChange_slot()
{
    QString currentSec = p_tw->getComboBoxSecurities()->currentText().toLower() + "_client";

    plotsDrawer->clearSecurityData();
    sqlSelector->selectData(currentSec);
    plotsDrawer->collectCandleInfo();
    plotsDrawer->p_candlesWidget->setCandlesData();
    plotsDrawer->p_verticalVolumeWidget->setCandlesData();
    plotsDrawer->p_horizontalVolumeWidget->setCandlesData();

    plotsDrawer->drawPlot();
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

