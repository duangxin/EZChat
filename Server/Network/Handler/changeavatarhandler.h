#ifndef CHANGEAVATARHANDLER_H
#define CHANGEAVATARHANDLER_H

#include "MsgHandler.h"

class changeAvatarHandler : public MsgHandler
{
public:
    explicit changeAvatarHandler(QObject *parent = nullptr);
    virtual void parse(Msg& msg, TcpClientSocket* socket = nullptr);
};

#endif // CHANGEAVATARHANDLER_H
