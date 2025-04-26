#ifndef LOGOUTHANDLER_H
#define LOGOUTHANDLER_H

#include "MsgHandler.h"

class logoutHandler : public MsgHandler
{
    Q_OBJECT
public:
    explicit logoutHandler(QObject* parent = nullptr);
    virtual void parse(Msg& msg, TcpClientSocket* socket = nullptr);
};

#endif // LOGOUTHANDLER_H
