#ifndef TCPCLIENTSOCKET_H
#define TCPCLIENTSOCKET_H
#include <QTcpSocket>
#include "DataModel/datamodel.h"

class TcpClientSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit TcpClientSocket(QObject* parent = nullptr);    //自动管理内存
    void setServerIP(const QString & serverIP);
    void setServerTcpPort(const quint16 &serverTcpPort);
    QString getServerIP();
    quint16 getServerPort();

    bool connectToServer();
    void sendMessage(Msg * message);


protected:
    QString m_serverIP;
    quint16 m_serverTcpPort;
};

#endif // TCPCLIENTSOCKET_H
