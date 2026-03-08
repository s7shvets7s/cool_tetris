#ifndef MYSERVER_H
#define MYSERVER_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QObject>
//#include <QTextEdit>

class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = nullptr): QTcpServer(parent) {};
protected:

    void incomingConnection(qintptr socketDescriptor) override {
        QTcpSocket *socket = new QTcpSocket(this);
        socket->setSocketDescriptor(socketDescriptor);

        connect(socket, &QTcpSocket::readyRead, this, &MyServer::onReadyRead);
        connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

        qDebug() << "Новый клиент подключен:" << socketDescriptor;
    }

private slots:
    void onReadyRead() {

        QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
        if (!socket) return;


        QByteArray data = socket->readAll();
        dataStorage.append(data);

        qDebug() << "Получены данные:" << data << "| Всего в массиве:" << dataStorage.size();
    }

private:
    QList<QByteArray> dataStorage;
};


#endif // MYSERVER_H
