#ifndef CHATMSGHANDLER_H
#define CHATMSGHANDLER_H

#include "MsgHandler.h"

class chatMsgHandler : public MsgHandler
{
    Q_OBJECT
public:
    explicit chatMsgHandler(QObject *parent = nullptr);
    virtual void parse(Msg& msg);

signals:
    void readyShowChatMsg(ChatMessage chat_msg);
};

#endif // CHATMSGHANDLER_H
