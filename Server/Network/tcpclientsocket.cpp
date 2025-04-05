#include "tcpclientsocket.h"

TcpClientSocket::TcpClientSocket(QObject *parent)
    : QTcpSocket{parent}
{
    connect(this, &QTcpSocket::readyRead, this, &TcpClientSocket::onReadyRead);
    connect(this, &QTcpSocket::disconnected, this, &TcpClientSocket::onDisconnected);

}

void TcpClientSocket::onReadyRead()
{
    QByteArray data = readAll(); // 简单读取（可拓展为粘包处理）
    emit dataReceived(data);
}

void TcpClientSocket::onDisconnected()
{
    emit clientDisconnected();
}
