#include "tcpclientsocket.h"

TcpClientSocket::TcpClientSocket(QObject *parent) :
    QTcpSocket(parent)
{
    //sendMessage是否成功
    connect(this, &QTcpSocket::bytesWritten, this, [](qint64 bytes) {
        qDebug() << bytes << " bytes written successfully.";
    });

}

void TcpClientSocket::setServerIP(const QString &serverIP)
{
    m_serverIP = serverIP;
}

void TcpClientSocket::setServerTcpPort(const quint16 &serverTcpPort)
{
    m_serverTcpPort = serverTcpPort;
}

QString TcpClientSocket::getServerIP()
{
    return m_serverIP;
}

quint16 TcpClientSocket::getServerPort()
{
    return m_serverTcpPort;
}

bool TcpClientSocket::connectToServer()
{
    abort();  // 终止当前连接，准备新连接

    connectToHost(QHostAddress(this->m_serverIP), this->m_serverTcpPort);

    if (waitForConnected(5000))  // 等待最多 5 秒
    {
        return true;  // 连接成功
    }
    else
    {
        return false;  // 连接失败
    }
}

void TcpClientSocket::sendMessage(Msg* message)
{
    write(message->toQByteArray());
    //这样会阻塞UI，改用信号与槽
    // waitForBytesWritten();  //阻塞等待数据写入到底层设备,防止在缓冲区还没发出去

}

