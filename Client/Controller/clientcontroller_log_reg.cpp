#include "clientcontroller.h"
#include "Utilities/encryption.h"

//注册
void ClientController::requestRegister(QString username, QString password){

    password = Encryption::GetHash(password);
    //密码做一次哈希

    UserInfo tmp = UserInfo(0x0000, username, password);

    connectToServer();

    getSocket()->sendMessage(new Msg(MsgType::REQUEST_REGISTER,tmp.toQByteArray()));
}
