#include "loginhandler.h"

loginHandler::loginHandler(QObject *parent)
    : MsgHandler{parent}
{}

void loginHandler::parse(Msg & msg){
    MsgType loginStatus = msg.getType();

    if(loginStatus == MsgType::LOGIN_SUCCESS){
        myInfo = UserInfo::fromQByteArray(msg.getContent());
        emit loginSuccessful(myInfo);
    }else{
        emit loginFailed();
    }
}

UserInfo& loginHandler::getMyInfo(){
    return myInfo;
}
