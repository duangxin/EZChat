#ifndef REGISTERHANDLER_H
#define REGISTERHANDLER_H

#include "MsgHandler.h"

class registerHandler : public MsgHandler
{
    Q_OBJECT
public:
    explicit registerHandler(QObject *parent = nullptr);
    virtual void parse(Msg& msg);

signals:
    void registerSuccessful(UserInfo info);
    void registerFailed();

};


#endif // REGISTERHANDLER_H
