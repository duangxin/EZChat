#ifndef SYNCMESSAGESHANDLER_H
#define SYNCMESSAGESHANDLER_H

#include "MsgHandler.h"

class syncMessagesHandler : public MsgHandler
{
public:
    explicit syncMessagesHandler(QObject *parent = nullptr);

    virtual void parse(Msg& msg, TcpClientSocket* socket = nullptr);
};

#endif // SYNCMESSAGESHANDLER_H
