#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>

//启动/关闭监听,,接受新连接，生成TcpClientSocket

class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = nullptr);

protected:
    void incomingConnection(qintptr socketDescriptor) override;
};

#endif // TCPSERVER_H
