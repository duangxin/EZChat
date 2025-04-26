#ifndef SYNCMESSAGESHANDLER_H
#define SYNCMESSAGESHANDLER_H

#include "MsgHandler.h"

class syncMessagesHandler : public MsgHandler
{
    Q_OBJECT
public:
    explicit syncMessagesHandler(QObject *parent = nullptr);
        virtual void parse(Msg& msg);
};
#endif // SYNCMESSAGESHANDLER_H
