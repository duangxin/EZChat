#include "deletefriendhandler.h"
#include <QDebug>

deleteFriendHandler::deleteFriendHandler(QObject *parent)
    : MsgHandler{parent}
{}

void deleteFriendHandler::parse(Msg &msg)
{
    emit readyShowResult(msg);
}
