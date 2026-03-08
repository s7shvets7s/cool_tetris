#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include <QObject>
#include <QTcpSocket>
class NetworkManager : public QObject
{
    Q_OBJECT
public:
    static NetworkManager& instance();
    void sendScore(const QString& nickname, int score, int lines);
    void setServerAddress(const QString& host, quint16 port);

signals:

    void sendSuccess();
    void sendError(const QString& error);
private:
    explicit NetworkManager(QObject* parent = nullptr);
    QString m_host;
    quint16 m_port;


};

#endif // NETWORK_MANAGER_H
