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

    MsgHandler * addfriendhandler = new addFriendHandler(this);
    newHandler(MsgType::REQUEST_ADD_FRIEND, addfriendhandler);

    MsgHandler * deletefriendhandler = new deleteFriendHandler(this);
    newHandler(MsgType::DELETE_FRIEND_SUCCESS, deletefriendhandler);
    newHandler(MsgType::DELETE_FRIEND_ERROR_NOFRIEND, deletefriendhandler);

    MsgHandler * friendlisthandler = new friendListHandler(this);
    newHandler(MsgType::ALL_FRIEND_LIST, friendlisthandler);

    MsgHandler * addfriendanswerhandler = new addFriendAnswerhandler(this);
    newHandler(MsgType::REQUEST_ADD_FRIEND_AGREED, addfriendanswerhandler);
    newHandler(MsgType::REQUEST_ADD_FRIEND_DECLINED, addfriendanswerhandler);
    newHandler(MsgType::REQUEST_ADD_FRIEND_ERROR_FRIEND_OFFLINE, addfriendanswerhandler);
    newHandler(MsgType::REQUEST_ADD_FRIEND_ERROR_FRIEND_NOT_EXIST, addfriendanswerhandler);
    newHandler(MsgType::REQUEST_ADD_FRIEND_ERROR_FRIENDSHIP_EXIST, addfriendanswerhandler);

    MsgHandler * changeavatarhandler = new changeAvatarHandler(this);
    newHandler(MsgType::MODIFY_AVATAR_SUCCESS, changeavatarhandler);
    newHandler(MsgType::MODIFY_AVATAR_ERROR, changeavatarhandler);

    MsgHandler * changenamehandler = new changeNameHandler(this);
    newHandler(MsgType::MODIFY_USERNAME_SUCCESS, changenamehandler);
    newHandler(MsgType::MODIFY_USERNAME_ERROR, changenamehandler);

    MsgHandler * chatmsghandler = new chatMsgHandler(this);
    newHandler(MsgType::MSG_TEXT, chatmsghandler);

    MsgHandler * syncmessagesHandler = new syncMessagesHandler(this);
    newHandler(MsgType::RETURN_SYNC_MESSAGES, syncmessagesHandler);
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
