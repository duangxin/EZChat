#include "clientcontroller.h"
#include "Utilities/encryption.h"
#include "Network/clienthandlerreg.h"


//注册
void ClientController::requestRegister(QString username, QString password){

    //密码做一次哈希
    password = Encryption::GetHash(password);
    UserInfo tmp(0x0000, username, password);
    auto message = std::make_unique<Msg>(MsgType::REQUEST_REGISTER, tmp.toQByteArray());

    sendMessageWhenConnected(std::move(message));
}
//登录
void ClientController::requestLogin(quint32 id, QString password){

    password = Encryption::GetHash(password);
    //密码做一次哈希

    UserInfo tmp(id, "", password);
    auto message = std::make_unique<Msg>(MsgType::REQUEST_LOGIN, tmp.toQByteArray());

    sendMessageWhenConnected(std::move(message));

}
//登出
void ClientController::requestLogout(quint32 id){

    UserInfo tmp(id, "", "");
    auto message = std::make_unique<Msg>(MsgType::REQUEST_LOGOUT, tmp.toQByteArray());

    sendMessageWhenConnected(std::move(message));

}

//获取登录用户
UserInfo& ClientController::getMyInfo(){
    loginHandler * tmp = (loginHandler *) ClientHandlerReg::GetInstance()->getHandler(MsgType::LOGIN_SUCCESS);
    return tmp->getMyInfo();
}
