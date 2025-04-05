#include "server.h"
#include <QMessageBox>
Server::Server(QObject *parent)
    : QObject{parent},
    m_tcpServer(new TcpServer)
{
    connect(m_tcpServer, &TcpServer::newClientConnected, this, &Server::onNewConnection);

}

void Server::start(int port)
{
    if (!m_tcpServer->listen(QHostAddress::Any, port)) {
        QMessageBox::warning(nullptr, "错误",
                             "无法监听端口，可能是该端口已被占用");
        qDebug() << "Server listen error:" << m_tcpServer->errorString();
        return; // 提前退出
    }

    qDebug() << "Server started, listening on port:" << port;
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

void Server::onNewConnection(QTcpSocket* socket) {
    auto client = qobject_cast<TcpClientSocket*>(socket);
    if (!client) return;

    quint32 id = m_clients.size() + 1;  // 简单分配ID
    addClient(id, client);

    connect(client, &TcpClientSocket::dataReceived, this, [=](QByteArray data){
        qDebug() << "收到客户端" << id << "的数据：" << data;
        // TODO：调用消息处理模块
    });

    connect(client, &TcpClientSocket::clientDisconnected, this, [=](){
        deleteClient(id);
        client->deleteLater();
        qDebug() << "客户端" << id << "断开连接";
    });

    qDebug() << "新客户端连接，分配ID：" << id;
}
