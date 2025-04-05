#include "tcpclientsocket.h"

TcpClientSocket::TcpClientSocket(QObject *parent) :
    QTcpSocket(parent)
{
    //服务器连接状态
    connect(this, &QTcpSocket::stateChanged, [](QAbstractSocket::SocketState state) {
        qDebug() << "Socket state changed:" << state;
    });

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

void TcpClientSocket::connectToServer()
{
    abort();  // 终止当前连接，准备新连接

    connectToHost(QHostAddress(this->m_serverIP), this->m_serverTcpPort);


}

void TcpClientSocket::sendMessage(Msg* message)
{
    if (this->state() == QAbstractSocket::ConnectedState) {
        write(message->toQByteArray());
        //这样会阻塞UI，改用信号与槽
        //waitForBytesWritten();  //阻塞等待数据写入到底层设备,防止在缓冲区还没发出去
    }


}

