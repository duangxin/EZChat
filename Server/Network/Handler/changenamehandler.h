#ifndef CHANGENAMEHANDLER_H
#define CHANGENAMEHANDLER_H

#include "MsgHandler.h"

class changeNameHandler : public MsgHandler
{
public:
    explicit changeNameHandler(QObject *parent = nullptr);
    virtual void parse(Msg& msg, TcpClientSocket* socket = nullptr);
};

#endif // CHANGENAMEHANDLER_H
