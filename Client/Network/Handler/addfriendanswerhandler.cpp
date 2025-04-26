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
        emit sigAddFriendSuccessful();
    }else{
        emit sigAddFriendFailed(msg.getType());
    }
}
