#include "registerhandler.h"
#include <QDebug>
registerHandler::registerHandler(QObject *parent)
    : MsgHandler{parent}
{}

void registerHandler::parse(Msg &msg)
{
    MsgType registerStatus = msg.getType();

    if(registerStatus == MsgType::REGISTER_SUCCESS){
        emit registerSuccessful(UserInfo::fromQByteArray(msg.getContent()));
    }else{
        emit registerFailed();

    }
}
