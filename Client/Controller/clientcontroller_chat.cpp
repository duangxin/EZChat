#include "clientcontroller.h"


void ClientController::sendChatMessage(quint32 receiver, QString content){
    ChatMessage chat_msg(getMyInfo().getID(), receiver, content);
    auto message = std::make_unique<Msg>(MsgType::MSG_TEXT,chat_msg.toQByteArray());
    sendMessageWhenConnected(std::move(message));
}

QList<ChatMessage> * ClientController::getChatMsg(quint32 id) {
    if(chatMsgMap.contains(id)){
        return chatMsgMap[id];
    }
    return nullptr;
}

void ClientController::requestSyncMessages()
{
    auto message = std::make_unique<Msg>(MsgType::REQUEST_SYNC_MESSAGES, QByteArray());
    sendMessageWhenConnected(std::move(message));
}
