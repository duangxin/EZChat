#include "addfriendanswerhandler.h"

addFriendAnswerhandler::addFriendAnswerhandler(QObject *parent)
    : MsgHandler{parent}
{}

void addFriendAnswerhandler::parse(Msg &msg, TcpClientSocket *socket)
{
    Record::getRecord()->writeRecord("[好友应答请求]尝试解析...");
    if (msg.getType() != MsgType::REQUEST_ADD_FRIEND_AGREED
        && msg.getType() != MsgType::REQUEST_ADD_FRIEND_DECLINED) {
        Record::getRecord()->writeRecord("好友应答Msg错误！");
        return;
    }

    ChatMessage tmp = ChatMessage::fromQByteArray(msg.getContent());
    auto dbHelper = MySqlHelper::GetInstance();
    auto * receiverSocket = ServerController::getServerInstance()->getClient(tmp.getSender());
    if(msg.getType() == MsgType::REQUEST_ADD_FRIEND_AGREED){
        Record::getRecord()->writeRecord("[好友应答请求]好友请求通过！");
        dbHelper->addFriendship(tmp.getSender(),tmp.getReceiver());
        dbHelper->addFriendship(tmp.getReceiver(),tmp.getSender());
        UserInfo info = dbHelper->selectUserInfoById(tmp.getReceiver());
        auto replyMsg = std::make_unique<Msg>(MsgType::REQUEST_ADD_FRIEND_AGREED,info.toQByteArray());
        ServerController::getCtrlInstance()->sendMessageWhenConnected(receiverSocket,std::move(replyMsg));
        return;
    }else if(msg.getType() == MsgType::REQUEST_ADD_FRIEND_DECLINED){
        Record::getRecord()->writeRecord("[好友应答请求]好友请求拒绝！");
        UserInfo info = dbHelper->selectUserInfoById(tmp.getReceiver());
        auto replyMsg = std::make_unique<Msg>(MsgType::REQUEST_ADD_FRIEND_DECLINED,info.toQByteArray());
        ServerController::getCtrlInstance()->sendMessageWhenConnected(receiverSocket,std::move(replyMsg));
    }
    if(receiverSocket == nullptr){
        Record::getRecord()->writeRecord("[好友应答请求]对方已离线");
        auto replyMsg = std::make_unique<Msg>(MsgType::REQUEST_ADD_FRIEND_ERROR_FRIEND_OFFLINE,"");
        ServerController::getCtrlInstance()->sendMessageWhenConnected(socket,std::move(replyMsg));
        return;
    }
}
