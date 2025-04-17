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
    void sendMessage(Msg * message);

signals:
    void messageReceived(QByteArray data);    // 收到完整数据包
    void clientDisconnected();             // 客户端断开连接

private slots:
    void receiveMessage();        // 接收数据
    void onDisconnected();     // 客户端断开

protected:
    quint32 m_blockSize;
};

#endif // TCPCLIENTSOCKET_H
