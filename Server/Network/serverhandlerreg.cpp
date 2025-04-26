#include "serverhandlerreg.h"
#include "Utilities/record.h"
#include <QDebug>

QMap<MsgType, MsgHandler * > ServerHandlerReg::handler_regs;
ServerHandlerReg * ServerHandlerReg::regObj = nullptr;

ServerHandlerReg::ServerHandlerReg(QObject *parent)
    : QObject{parent}
{
    MsgHandler * registerhandler = new registerHandler(this);
    newHandler(MsgType::REQUEST_REGISTER, registerhandler);

    MsgHandler * loginhandler = new loginHandler(this);
    newHandler(MsgType::REQUEST_LOGIN, loginhandler);

    MsgHandler * logouthandler = new logoutHandler(this);
    newHandler(MsgType::REQUEST_LOGOUT, logouthandler);

    MsgHandler * addfriendhandler = new addFriendHandler(this);
    newHandler(MsgType::REQUEST_ADD_FRIEND, addfriendhandler);


    MsgHandler * deletefriendhandler = new deleteFriendHandler(this);
    newHandler(MsgType::REQUEST_DELETE_FRIEND, deletefriendhandler);

    MsgHandler * friendlisthandler = new friendListHandler(this);
    newHandler(MsgType::REQUEST_ALL_FRIEND_LIST, friendlisthandler);

    MsgHandler * addfriendanswerhandler = new addFriendAnswerhandler(this);
    newHandler(MsgType::REQUEST_ADD_FRIEND_AGREED, addfriendanswerhandler);
    newHandler(MsgType::REQUEST_ADD_FRIEND_DECLINED, addfriendanswerhandler);

    MsgHandler * changeavatarhandler = new changeAvatarHandler(this);
    newHandler(MsgType::MODIFY_AVATAR, changeavatarhandler);

    MsgHandler * changenamehandler = new changeNameHandler(this);
    newHandler(MsgType::MODIFY_USERNAME, changenamehandler);

    MsgHandler * chatmsghandler = new chatMsgHandler(this);
    newHandler(MsgType::MSG_TEXT, chatmsghandler);

    MsgHandler * syncmessagesHandler = new syncMessagesHandler(this);
    newHandler(MsgType::REQUEST_SYNC_MESSAGES, syncmessagesHandler);
}

//单例
ServerHandlerReg * ServerHandlerReg::GetInstance(){
    if(!regObj){
        regObj = new ServerHandlerReg();
    }
    return regObj;
}


MsgHandler * ServerHandlerReg::getHandler(MsgType type){
    if(handler_regs.contains(type)){    //查找map
        return handler_regs[type];
    }else{
        qDebug() << static_cast<quint16>(type);

        Record::getRecord()->writeRecord(QString("未找到对应类型的handler!"));
    }
    return nullptr;
}

void ServerHandlerReg::newHandler(MsgType type, MsgHandler *msg_handler)
{
    handler_regs[type] = msg_handler;
}
