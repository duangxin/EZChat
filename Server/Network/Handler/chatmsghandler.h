#ifndef CHATMSGHANDLER_H
#define CHATMSGHANDLER_H

#include "MsgHandler.h"

class chatMsgHandler : public MsgHandler
{
public:
    explicit chatMsgHandler(QObject *parent = nullptr);
    virtual void parse(Msg& msg, TcpClientSocket* socket = nullptr);
};

#endif // CHATMSGHANDLER_H
