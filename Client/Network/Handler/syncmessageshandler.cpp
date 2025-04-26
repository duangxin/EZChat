#include "syncmessageshandler.h"
#include "database.h"
#include <QDebug>

syncMessagesHandler::syncMessagesHandler(QObject *parent)
    : MsgHandler{parent}
{}

void syncMessagesHandler::parse(Msg &msg)
{
    //验证消息类型
    if (msg.getType() != MsgType::RETURN_SYNC_MESSAGES) {
        qDebug() << "[同步消息处理器]收到错误的消息类型！";
        return;
    }
    qDebug() << "[syncMessagesHandler] parse 被调用啦";
    // 获取 DataBase 实例
    DataBase::GetInstance()->syncMessagesFromServer(msg.getContent());

}
