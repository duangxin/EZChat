#include "servercontroller.h"


Server* ServerController::m_server = nullptr;

ServerController::ServerController()
{
}

//客户端控制器的单例
ServerController* ServerController::obj = nullptr;

ServerController* ServerController::getCtrlInstance() {
    if (!obj) {
        obj = new ServerController();
    }
    return obj;
}

Server* ServerController::getServerInstance()
{
    if (!m_server) {
        m_server = new Server();
    }
    return m_server;
}
void ServerController::sendMessageWhenConnected(TcpClientSocket* socket, std::unique_ptr<Msg> msg)
{
    if (socket->state() == QAbstractSocket::ConnectedState) {
        // 如果连接已建立，直接发送消息
        socket->sendMessage(msg.get());
    } else {
        // 如果连接未建立，缓存消息并等待连接成功
        connect(socket, &QTcpSocket::connected, this, [socket, msg = std::move(msg)]() {
            socket->sendMessage(msg.get());  // 连接成功后发送消息

        });
    }
}
