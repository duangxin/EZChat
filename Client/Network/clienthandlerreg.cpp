#include "clienthandlerreg.h"
#include "msgType.h"

QMap<MsgType, MsgHandler *> ClientHandlerReg::handler_regs;
ClientHandlerReg * ClientHandlerReg::regObj = nullptr;

ClientHandlerReg::ClientHandlerReg(QObject *parent)
    : QObject{parent}
{
    MsgHandler* registerhandler = new registerHandler(this);
    newHandler(MsgType::REGISTER_SUCCESS, registerhandler);
    newHandler(MsgType::REGISTER_ERROR, registerhandler);

    MsgHandler * loginhandler = new loginHandler(this);
    newHandler(MsgType::LOGIN_SUCCESS, loginhandler);
    newHandler(MsgType::LOGIN_ERROR, loginhandler);
}

//单例
ClientHandlerReg * ClientHandlerReg::GetInstance(){
    if(!regObj){
        regObj = new ClientHandlerReg();
    }
    return regObj;
}


MsgHandler * ClientHandlerReg::getHandler(MsgType type){
    if(handler_regs.contains(type)){    //查找map
        return handler_regs[type];
    }
    return nullptr;
}

void ClientHandlerReg::newHandler(MsgType type, MsgHandler *msg_handler)
{
    handler_regs[type] = msg_handler;
}
