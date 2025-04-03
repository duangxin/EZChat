#include "clientcontroller.h"



ClientController::ClientController(QObject* parent) : QObject(parent){

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
    if (socket == NULL) {
        socket = std::make_unique<TcpClientSocket>();
    }
    //智能指针要用.get()返回TcpClientSocket*类型
    return socket.get();
}

QString ClientController::IP = "192.168.6.6";

void ClientController::connectToServer()
{
    TcpClientSocket* clientSocket = getSocket();
    clientSocket->setServerIP(IP);
    clientSocket->setServerTcpPort(6666);
    if (!clientSocket->connectToServer()) {
        qDebug() << "[connectToServer] Connection Failed.";
    }
    else {
        qDebug() << "[connectToServer] Connection Successful.";
    }
}


