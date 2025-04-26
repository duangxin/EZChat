#include "logouthandler.h"

logoutHandler::logoutHandler(QObject *parent)
    : MsgHandler{parent}
{}

void logoutHandler::parse(Msg &msg, TcpClientSocket *socket)
{
    Record::getRecord()->writeRecord("[登出请求]尝试解析...");
    if (msg.getType() != MsgType::REQUEST_LOGOUT) {
        Record::getRecord()->writeRecord("登出Msg错误！");
        return;
    }
    UserInfo tmp = UserInfo::fromQByteArray(msg.getContent());
    if(ServerController::getServerInstance()->getClient(tmp.getID()) == nullptr){
        socket->sendMessage(new Msg(MsgType::LOGOUT_ERROR,""));
    }
    ServerController::getServerInstance()->deleteClient(tmp.getID());
    socket->sendMessage(new Msg(MsgType::LOGOUT_SUCCESS,""));
    Record::getRecord()->writeRecord(QString("[登出请求]用户[%1]登出成功！").arg(tmp.getID()));
}
