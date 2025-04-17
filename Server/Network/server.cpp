#include "server.h"
#include "Utilities/record.h"
#include <QMessageBox>
#include <QNetworkInterface>
#include "msg.h"
#include "userinfo.h"
Server::Server(QObject *parent)
    : QObject{parent},
    m_tcpServer(new TcpServer)
{

}

void Server::start(int port)
{
    if (!m_tcpServer->listen(QHostAddress::Any, port)) {
        QMessageBox::warning(nullptr, "错误",
                             "无法监听端口，可能是该端口已被占用");
        Record::getRecord()->writeRecord( "Server listen error:" + m_tcpServer->errorString());
        return; // 提前退出
    }
    Record::getRecord()->writeRecord( "服务器启动,监听端口:" + QString::number(port));

    //显示可用的IP
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && !address.isLoopback())
            Record::getRecord()->writeRecord( "服务器可连接 IP：" + address.toString());
    }
}

void Server::stop()
{
    // 主动关闭所有客户端连接
    for (auto socket : m_clients) {
        if (socket) {
            socket->disconnectFromHost();
            socket->close(); // 保底
            socket->deleteLater(); // 延迟释放，防止正在处理事件
        }
    }
    m_clients.clear();
    m_tcpServer->close();
}

void Server::addClient(quint32 id, TcpClientSocket *client)
{
    m_clients.insert(id, client);
}

void Server::deleteClient(quint32 id)
{
    m_clients.remove(id);
}

TcpClientSocket *Server::getClient(quint32 id)
{
    return m_clients.contains(id) ? m_clients.value(id) : nullptr;
}

