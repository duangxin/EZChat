#include "addfriendhandler.h"
#include <QDebug>

addFriendHandler::addFriendHandler(QObject *parent)
    : MsgHandler{parent}
{}

void addFriendHandler::parse(Msg &msg, TcpClientSocket *socket)
{
    Record::getRecord()->writeRecord("[添加好友请求]尝试解析...");
    if (msg.getType() != MsgType::REQUEST_ADD_FRIEND) {
        Record::getRecord()->writeRecord("添加好友Msg错误！");
        return;
    }

    ChatMessage tmp = ChatMessage::fromQByteArray(msg.getContent());
    auto dbHelper = MySqlHelper::GetInstance();
    if(dbHelper->selectUserInfoById(tmp.getReceiver()).getID()==0x0000){
        Record::getRecord()->writeRecord("[添加好友请求]用户不存在！");
        auto replyMsg = std::make_unique<Msg>(MsgType::REQUEST_ADD_FRIEND_ERROR_FRIEND_NOT_EXIST,"");
        ServerController::getCtrlInstance()->sendMessageWhenConnected(socket,std::move(replyMsg));
        return;
    }else if(dbHelper->friendshipExist(tmp.getSender(),tmp.getReceiver())){
        Record::getRecord()->writeRecord("[添加好友请求]您和对方已经是好友！");
        auto replyMsg = std::make_unique<Msg>(MsgType::REQUEST_ADD_FRIEND_ERROR_FRIENDSHIP_EXIST,"");
        ServerController::getCtrlInstance()->sendMessageWhenConnected(socket,std::move(replyMsg));
        return;
    }
    qDebug()<<tmp.getSender();
        qDebug()<<tmp.getReceiver();

    //找到对方的客户端
    auto Friend = ServerController::getServerInstance()->getClient(tmp.getReceiver());
    if(Friend == nullptr){
        Record::getRecord()->writeRecord("[添加好友请求]对方离线！");
        auto replyMsg = std::make_unique<Msg>(MsgType::REQUEST_ADD_FRIEND_ERROR_FRIEND_OFFLINE,"");
        ServerController::getCtrlInstance()->sendMessageWhenConnected(socket,std::move(replyMsg));
        return;
    }
    //进行转发
    Record::getRecord()->writeRecord("[添加好友请求]已转发给对方用户！");
    auto user = dbHelper->selectUserInfoById(tmp.getSender());
    auto replyMsg = std::make_unique<Msg>(MsgType::REQUEST_ADD_FRIEND,user.toQByteArray());
    ServerController::getCtrlInstance()->sendMessageWhenConnected(Friend,std::move(replyMsg));
}
