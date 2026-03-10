#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
    #include <QFileInfo>

class SimpleServer : public QTcpServer {
    Q_OBJECT
public:
    SimpleServer(QObject *parent = nullptr) : QTcpServer(parent) {}

protected:
    void incomingConnection(qintptr socketDescriptor) override {
        QTcpSocket* socket = new QTcpSocket(this);
        socket->setSocketDescriptor(socketDescriptor);

        qDebug() << "Клиент подключился:" << socket->peerAddress().toString();

        connect(socket, &QTcpSocket::readyRead, this, [socket]() {
            QByteArray data = socket->readAll();


            QJsonDocument doc = QJsonDocument::fromJson(data.trimmed());
            if (doc.isNull() || !doc.isObject()) {
                qDebug() << "Ошибка: Получены некорректные данные";
                return;
            }

            QJsonObject json = doc.object();
            QString nickname = json["nickname"].toString();
            int score = json["score"].toInt();

            qDebug() << "Данные игрока -> Имя:" << nickname << "Счёт:" << score;


            QSqlQuery query;
            query.prepare("INSERT INTO TopResults (nickname, BestScore) VALUES (:name, :score)");
            query.bindValue(":name", nickname);
            query.bindValue(":score", score);

            if (!query.exec()) {
                qDebug() << "Ошибка записи в БД:" << query.lastError().text();
                socket->write("ERROR\n");
            } else {
                qDebug() << "Запись успешно добавлена";
                socket->write("OK\n");
            }
        });

        connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
        connect(socket, &QTcpSocket::disconnected, []() {
            qDebug() << "Клиент отключился";
        });
    }
};

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);


    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("testDB.db");

    if (!db.open()) {
        qDebug() << "Критическая ошибка: не удалось открыть БД:" << db.lastError().text();
        return -1;
    }
    qDebug() << "База данных подключена.";


    QSqlQuery query;
    bool tableOk = query.exec("CREATE TABLE IF NOT EXISTS TopResults ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                              "nickname TEXT, "
                              "BestScore INT)");
    if (!tableOk) {
        qDebug() << "Ошибка создания таблицы:" << query.lastError().text();
    }


    SimpleServer server;
    if (!server.listen(QHostAddress::Any, 5000)) {
        qDebug() << "Ошибка запуска сервера:" << server.errorString();
        return 1;
    }

    qDebug() << "Сервер Tetris запущен на порту 5000";
    qDebug() << "Путь к БД:" << QFileInfo(db.databaseName()).absoluteFilePath();
    return app.exec();
}
#include "main.moc"

