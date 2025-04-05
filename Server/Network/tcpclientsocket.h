#ifndef TCPCLIENTSOCKET_H
#define TCPCLIENTSOCKET_H

#include <QTcpSocket>
#include "msg.h"

//和一个客户端通信（收发消息）

class TcpClientSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit TcpClientSocket(QObject *parent = nullptr);

signals:
    void dataReceived(QByteArray data);    // 收到完整数据包
    void clientDisconnected();             // 客户端断开连接

private slots:
    void onReadyRead();        // 数据到达
    void onDisconnected();     // 客户端断开
};

#endif // TCPCLIENTSOCKET_H
