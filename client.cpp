// client.cpp
#include "client.h"

Client::Client(QWidget *parent) : QWidget(parent)
{
    socket = new QTcpSocket(this);

    connect(socket, &QTcpSocket::readyRead, this, &Client::readyRead);
    connect(socket, &QTcpSocket::connected, this, &Client::connected);
    connect(socket, &QTcpSocket::disconnected, this, &Client::disconnected);
}

void Client::connectToServer(const QString &host, quint16 port)
{
    socket->connectToHost(host, port);
}

void Client::sendMessage(const QString &message)
{
    if (socket->state() == QTcpSocket::ConnectedState) {
        socket->write(message.toUtf8());
    }
}

void Client::readyRead()
{
    QByteArray data = socket->readAll();
    emit messageReceived(QString(data));
}

void Client::connected()
{
    qDebug() << "Connected to server";
}

void Client::disconnected()
{
    qDebug() << "Disconnected from server";
}


