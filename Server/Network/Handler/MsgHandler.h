#ifndef MSGHANDLER_H
#define MSGHANDLER_H


#include <QObject>
#include "msg.h"
#include "Network/tcpclientsocket.h"


//MsgHandler接口(抽象类), 用于定义对Msg共同的parse行为.

class MsgHandler : public QObject
{
    Q_OBJECT
public:
    explicit MsgHandler(QObject* parent = nullptr) : QObject(parent){};
    //解析Msg的纯虚函数，，子类必须重写
    virtual void parse(Msg& msg, TcpClientSocket* socket = nullptr) = 0;
};

#endif // MSGHANDLER_H
