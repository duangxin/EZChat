#ifndef DELETEFRIENDHANDLER_H
#define DELETEFRIENDHANDLER_H

#include "MsgHandler.h"

class deleteFriendHandler : public MsgHandler
{
    Q_OBJECT
public:
    explicit deleteFriendHandler(QObject *parent = nullptr);
    virtual void parse(Msg& msg, TcpClientSocket* socket = nullptr);
};

#endif // DELETEFRIENDHANDLER_H
