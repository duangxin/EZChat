#include "chatmsghandler.h"

chatMsgHandler::chatMsgHandler(QObject *parent)
    : MsgHandler{parent}
{}

void chatMsgHandler::parse(Msg &msg, TcpClientSocket *socket)
{
    Record::getRecord()->writeRecord("[发送消息请求]尝试解析...");
    if (msg.getType() != MsgType::MSG_TEXT) {
        Record::getRecord()->writeRecord("发送消息Msg错误！");
        return;
    }
    //内容转为chatmessage格式处理
    ChatMessage tmp = ChatMessage::fromQByteArray(msg.getContent());
    auto dbHelper = MySqlHelper::GetInstance();
    dbHelper->addMsg(tmp.getSender(), tmp.getReceiver(), tmp.getContent(), tmp.getTimeStamp());
    auto * receiverSocket = ServerController::getServerInstance()->getClient(tmp.getReceiver());
    if (receiverSocket == nullptr){
        Record::getRecord()->writeRecord("[发送消息请求]对方不在线！");
        dbHelper->addOfflineMsg(tmp);

    }else{
        Record::getRecord()->writeRecord("[发送消息请求]正在转发消息！");
        auto replyMsg = std::make_unique<Msg>(MsgType::MSG_TEXT,tmp.toQByteArray());
        ServerController::getCtrlInstance()->sendMessageWhenConnected(receiverSocket,std::move(replyMsg));
    }

    Record::getRecord()->writeRecord("[发送消息请求]处理完成！");
}
