#ifndef ADDFRIENDHANDLER_H
#define ADDFRIENDHANDLER_H

#include "MsgHandler.h"

class addFriendHandler : public MsgHandler
{
    Q_OBJECT
public:
    explicit addFriendHandler(QObject *parent = nullptr);
    virtual void parse(Msg& msg, TcpClientSocket* socket = nullptr);
};

#endif // ADDFRIENDHANDLER_H
