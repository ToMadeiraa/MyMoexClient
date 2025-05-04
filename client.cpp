#include "client.h"

Client::Client(QWidget *parent) : QWidget(parent)
{
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




}

