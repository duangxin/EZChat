#ifndef SERVERHANDLERREG_H
#define SERVERHANDLERREG_H

#include <QObject>
#include "Handler/MsgHandler.h"
#include "Handler/registerhandler.h"
#include "Handler/loginhandler.h"
#include "Handler/addfriendhandler.h"
#include "Handler/addfriendanswerhandler.h"
#include "Handler/friendlisthandler.h"

class ServerHandlerReg : public QObject
{
    Q_OBJECT
public:
    explicit ServerHandlerReg(QObject *parent = nullptr);

    static ServerHandlerReg * GetInstance();
    MsgHandler * getHandler(MsgType);
private:
    void newHandler(MsgType type, MsgHandler * msg_handler);
    //Handler注册表Map
    static QMap<MsgType, MsgHandler *> handler_regs;
    static ServerHandlerReg * regObj;

signals:
};

#endif // SERVERHANDLERREG_H
