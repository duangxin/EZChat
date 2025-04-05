#include "clientcontroller.h"
#include "Utilities/encryption.h"


//注册
void ClientController::requestRegister(QString username, QString password){

    //密码做一次哈希
    password = Encryption::GetHash(password);

    UserInfo tmp = UserInfo(0x0000, username, password);

    connectToServer();

    getSocket()->sendMessage(std::make_unique<Msg>
                             (MsgType::REQUEST_REGISTER, tmp.toQByteArray())
                                 .get());
}
