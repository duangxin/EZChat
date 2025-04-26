#ifndef CHANGEAVATARHANDLER_H
#define CHANGEAVATARHANDLER_H

#include "MsgHandler.h"

class changeAvatarHandler : public MsgHandler
{
        Q_OBJECT
public:
    explicit changeAvatarHandler(QObject *parent = nullptr);
    virtual void parse(Msg& msg);
signals:
    void modifyAvatarSuccess(UserInfo info);
    void modifyAvatarFail();
};

#endif // CHANGEAVATARHANDLER_H
