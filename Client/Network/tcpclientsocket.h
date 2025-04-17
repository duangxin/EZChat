#ifndef TCPCLIENTSOCKET_H
#define TCPCLIENTSOCKET_H
#include <QTcpSocket>
#include "datamodel.h"

class TcpClientSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit TcpClientSocket(QObject* parent = nullptr);    //自动管理内存
    void setServerIP(const QString & serverIP);
    void setServerTcpPort(const quint16 &serverTcpPort);
    QString getServerIP();
    quint16 getServerPort();

    void connectToServer();
    void sendMessage(Msg * message);

private slots:
    void receiveMessage();        // 接收数据


protected:
    QString m_serverIP;
    quint16 m_serverTcpPort;
    quint32 m_blockSize = 0;
};

#endif // TCPCLIENTSOCKET_H
