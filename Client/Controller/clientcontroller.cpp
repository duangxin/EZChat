#include "clientcontroller.h"
#include "Utilities/config.h"

ClientController::ClientController(QObject* parent) : QObject(parent){



    //登录成功时 初始化聊天信息Map 以及获取好友列表
    connect((loginHandler*)ClientHandlerReg::GetInstance()->getHandler(MsgType::LOGIN_SUCCESS),
            &loginHandler::loginSuccessful,
            this,&ClientController::requestFriendList);


}

//客户端控制器的单例
ClientController* ClientController::obj = nullptr;

ClientController* ClientController::getClientInstance() {
    if (!obj) {
        obj = new ClientController();
    }
    return obj;
}

//客户端socket
TcpClientSocket* ClientController::getSocket() {
    if (socket == nullptr) {
        socket = std::make_unique<TcpClientSocket>();
    }
    //智能指针要用.get()返回TcpClientSocket*类型
    return socket.get();
}

void ClientController::sendMessageWhenConnected(std::unique_ptr<Msg> msg)
{
    if (getSocket()->state() == QAbstractSocket::ConnectedState) {
        // 如果已经连接，直接发送消息
        getSocket()->sendMessage(msg.get());
    } else {
        // 如果没有连接，缓存消息并等待连接成功
        connect(getSocket(), &QTcpSocket::connected, this, [this, msg = std::move(msg)]() {
            getSocket()->sendMessage(msg.get());
        });

        // 确保只执行一次连接
        if (getSocket()->state() != QAbstractSocket::ConnectingState &&
            getSocket()->state() != QAbstractSocket::ConnectedState) {
            connectToServer(); // 执行连接操作
        }
    }
}

void ClientController::connectToServer()
{
    TcpClientSocket* clientSocket = getSocket();
    clientSocket->setServerIP(SERVER_IP);
    clientSocket->setServerTcpPort(SERVER_PORT);
    clientSocket->connectToServer();

}


