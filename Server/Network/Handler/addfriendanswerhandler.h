#ifndef ADDFRIENDANSWERHANDLER_H
#define ADDFRIENDANSWERHANDLER_H

#include "MsgHandler.h"

class addFriendAnswerhandler : public MsgHandler
{
    Q_OBJECT
public:
    explicit addFriendAnswerhandler(QObject *parent = nullptr);

    virtual void parse(Msg& msg, TcpClientSocket* socket = nullptr);
};

#endif // ADDFRIENDANSWERHANDLER_H
