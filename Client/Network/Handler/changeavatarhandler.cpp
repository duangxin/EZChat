#include "changeavatarhandler.h"

changeAvatarHandler::changeAvatarHandler(QObject *parent)
    : MsgHandler{parent}
{}

void changeAvatarHandler::parse(Msg &msg)
{
    if (msg.getType() == MsgType::MODIFY_AVATAR_SUCCESS) {

        emit modifyAvatarSuccess(UserInfo::fromQByteArray(msg.getContent()));
    }
    else if (msg.getType() == MsgType::MODIFY_AVATAR_ERROR) {
        emit modifyAvatarFail();
    }
}
