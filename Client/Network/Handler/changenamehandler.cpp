#include "changenamehandler.h"
#include <QDebug>
changeNameHandler::changeNameHandler(QObject *parent)
    : MsgHandler{parent}
{}

void changeNameHandler::parse(Msg &msg)
{

    if (msg.getType() == MsgType::MODIFY_USERNAME_SUCCESS) {

        emit modifyUserNameSuccess(UserInfo::fromQByteArray(msg.getContent()));
    }
    else if (msg.getType() == MsgType::MODIFY_USERNAME_ERROR) {
        emit modifyUserNameFail();
    }
}
