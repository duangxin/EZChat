#include "tcpserver.h"
#include "Network/tcpclientsocket.h"

TcpServer::TcpServer(QObject *parent)
    : QTcpServer{parent}
{}

//incommingConnection是关键函数，重载它用于接收连接
void TcpServer::incomingConnection ( qintptr socketDescriptor )
{
    TcpClientSocket *tcpClientSocket = new TcpClientSocket(this);
    //告诉TcpClientSocket它要处理哪个客户端的连接，设置本socket唯一标识符
    tcpClientSocket->setSocketDescriptor(socketDescriptor);

    //发给Server 管理
    emit newClientConnected(tcpClientSocket);
}
