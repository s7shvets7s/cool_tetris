#include "network_manager.h"
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

NetworkManager::NetworkManager(QObject* parent)
    : QObject(parent), m_host("127.0.0.1"), m_port(5000) {}

NetworkManager& NetworkManager::instance() {
    static NetworkManager instance;
    return instance;
}

void NetworkManager::setServerAddress(const QString& host, quint16 port) {
    m_host = host;
    m_port = port;
}

void NetworkManager::sendScore(const QString& nickname, int score, int lines) {
    QTcpSocket* socket = new QTcpSocket();

    QObject::connect(socket, &QTcpSocket::connected, [=]() {
        QJsonObject json{
            {"type", "score"},
            {"nickname", nickname},
            {"score", score},
            {"lines", lines}
        };
        socket->write(QJsonDocument(json).toJson(QJsonDocument::Compact) + "\n");
    });

    QObject::connect(socket, &QTcpSocket::readyRead, [=]() {
        qDebug() << "Сервер ответил:" << socket->readAll();
        emit sendSuccess();
        socket->deleteLater();
    });

    QObject::connect(socket, &QTcpSocket::errorOccurred, [=]() {
        emit sendError(socket->errorString());
        socket->deleteLater();
    });

    socket->connectToHost(m_host, m_port);
}
