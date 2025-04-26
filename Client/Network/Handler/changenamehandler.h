#ifndef CHANGENAMEHANDLER_H
#define CHANGENAMEHANDLER_H

#include "MsgHandler.h"

class changeNameHandler : public MsgHandler
{
    Q_OBJECT
public:
    explicit changeNameHandler(QObject *parent = nullptr);
    virtual void parse(Msg& msg);

signals:
    void modifyUserNameSuccess(UserInfo info);
    void modifyUserNameFail();
};

#endif // CHANGENAMEHANDLER_H
