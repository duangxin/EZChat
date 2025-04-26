#include "addfriendhandler.h"
#include <QDebug>

addFriendHandler::addFriendHandler(QObject *parent)
    : MsgHandler{parent}
{}

void addFriendHandler::parse(Msg &msg)
{
    //收到好友请求
    UserInfo nowMst =  UserInfo::fromQByteArray(msg.getContent());
    emit readyShowFriendRequest(nowMst);
}
