#include "chatmsghandler.h"
#include "GUI/login.h"
#include "Controller/clientcontroller.h"

chatMsgHandler::chatMsgHandler(QObject *parent)
    : MsgHandler{parent}
{}

void chatMsgHandler::parse(Msg &msg)
{
    ChatMessage chat_msg = ChatMessage::fromQByteArray(msg.getContent());
    QList<ChatMessage> * list =ClientController::getClientInstance()->getChatMsg(chat_msg.getSender());
    if(list) {//只有是好友的时候才收消息
        list->append(chat_msg);
        emit readyShowChatMsg(chat_msg);
        return;
    }


}
