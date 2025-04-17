#ifndef SERVER_H
#define SERVER_H

#include <QObject>

#include "Network/tcpclientsocket.h"
#include "Network/tcpserver.h"
#include <QMap>

//总的调度器，负责启动服务器，管理所有客户端的连接
class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    void start(int port);              // 启动服务
    void stop();                       // 停止服务
    void addClient(quint32 id, TcpClientSocket* client);
    void deleteClient(quint32 id);
    TcpClientSocket* getClient(quint32 id);

signals:

private:
    TcpServer* m_tcpServer;
    QMap<quint32,TcpClientSocket*> m_clients;
};

#endif // SERVER_H
