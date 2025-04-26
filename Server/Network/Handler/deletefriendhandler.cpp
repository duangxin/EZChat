#include "deletefriendhandler.h"

deleteFriendHandler::deleteFriendHandler(QObject *parent)
    : MsgHandler{parent}
{}

void deleteFriendHandler::parse(Msg &msg, TcpClientSocket *socket)
{
    Record::getRecord()->writeRecord("[删除好友请求]尝试解析...");
    if (msg.getType() != MsgType::REQUEST_DELETE_FRIEND) {
        Record::getRecord()->writeRecord("删除好友Msg错误！");
        return;
    }
    ChatMessage tmp = ChatMessage::fromQByteArray(msg.getContent());
    auto dbHelper = MySqlHelper::GetInstance();
    if(dbHelper->friendshipExist(tmp.getSender(),tmp.getReceiver())){
        Record::getRecord()->writeRecord("[删除好友请求]好友关系已取消！");
        dbHelper->deleteFriendship(tmp.getSender(),tmp.getReceiver());
        UserInfo info = dbHelper->selectUserInfoById(tmp.getReceiver());
        auto replyMsg = std::make_unique<Msg>(MsgType::DELETE_FRIEND_SUCCESS,info.toQByteArray());
        ServerController::getCtrlInstance()->sendMessageWhenConnected(socket,std::move(replyMsg));
        return;
    }
    Record::getRecord()->writeRecord("[删除好友请求]好友关系不存在！");
    auto replyMsg = std::make_unique<Msg>(MsgType::DELETE_FRIEND_ERROR_NOFRIEND,"");
    ServerController::getCtrlInstance()->sendMessageWhenConnected(socket,std::move(replyMsg));
}
