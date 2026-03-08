#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <iostream>
#include <windows.h>
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    QByteArray localMsg = msg.toLocal8Bit();
    std::cout << localMsg.constData() << std::endl;
}
class SimpleServer : public QTcpServer {
    void incomingConnection(qintptr socketDescriptor) override {
        QTcpSocket* socket = new QTcpSocket(this);
        socket->setSocketDescriptor(socketDescriptor);

        qDebug() << "Клиент подключился:" << socket->peerAddress();

        QObject::connect(socket, &QTcpSocket::readyRead, [=]() {
            QByteArray data = socket->readAll();
            qDebug() << "Получено:" << data;

            // Парсим JSON
            QJsonDocument doc = QJsonDocument::fromJson(data.trimmed());
            QJsonObject json = doc.object();

            qDebug() << "Игрок:" << json["nickname"].toString()
                     << "Счёт:" << json["score"].toInt()
                     << "Линии:" << json["lines"].toInt();

            socket->write("OK\n");
        });

        QObject::connect(socket, &QTcpSocket::disconnected, [=]() {
            qDebug() << "Клиент отключился";
            socket->deleteLater();
        });
    }
};

int main(int argc, char *argv[]) {
// #ifdef Q_OS_WIN

//     if (AllocConsole()) {

//         FILE* fp;
//         freopen_s(&fp, "CONOUT$", "w", stdout);
//         freopen_s(&fp, "CONOUT$", "w", stderr);
//         freopen_s(&fp, "CONIN$", "r", stdin);


//         std::ios::sync_with_stdio();
//     }
// #endif
    QCoreApplication app(argc, argv);
    //qInstallMessageHandler(myMessageOutput);
    SimpleServer server;
    if (!server.listen(QHostAddress::LocalHost, 5000)) {
        qDebug() << "Ошибка запуска сервера:" << server.errorString();
        return 1;
    }

    qDebug() << "Сервер запущен на порту 5000";

    return app.exec();
}
