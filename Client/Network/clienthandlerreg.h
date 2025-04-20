#ifndef CLIENTHANDLERREG_H
#define CLIENTHANDLERREG_H

#include <QObject>
#include <QMap>
#include "Handler/MsgHandler.h"
#include "Handler/registerhandler.h"
#include "Handler/loginhandler.h"
#include "Handler/addfriendhandler.h"
#include "Handler/addfriendanswerhandler.h"
#include "Handler/friendlisthandler.h"

class ClientHandlerReg : public QObject
{
    Q_OBJECT
public:
    explicit ClientHandlerReg(QObject *parent = nullptr);

    static ClientHandlerReg * GetInstance();
    MsgHandler * getHandler(MsgType);
private:
    void newHandler(MsgType type, MsgHandler * msg_handler);
    //Handler注册表Map
    static QMap<MsgType, MsgHandler *> handler_regs;
    static ClientHandlerReg * regObj;

signals:
};

#endif // CLIENTHANDLERREG_H
