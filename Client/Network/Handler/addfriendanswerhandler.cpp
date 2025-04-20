#include "addfriendanswerhandler.h"
#include "Controller/clientcontroller.h"

addFriendAnswerhandler::addFriendAnswerhandler(QObject *parent)
    : MsgHandler{parent}
{}

void addFriendAnswerhandler::parse(Msg &msg)
{
    if(msg.getType() == MsgType::REQUEST_ADD_FRIEND_AGREED){
        UserInfo u = UserInfo::fromQByteArray(msg.getContent());
        ClientController::getClientInstance()->dynamicAppendFriend(u);
        //这样只需要缓存头像就行了.
        emit sigAddFriendSuccessful();
    }else{
        emit sigAddFriendFailed(msg.getType());
    }
}
