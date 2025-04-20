#ifndef FRIENDLISTHANDLER_H
#define FRIENDLISTHANDLER_H

#include "MsgHandler.h"

class friendListHandler : public MsgHandler
{
    Q_OBJECT
public:
    explicit friendListHandler(QObject *parent = nullptr);
    virtual void parse(Msg& msg);
signals:
    void sigFriendListGotcha(UserInfo info);
};

#endif // FRIENDLISTHANDLER_H
