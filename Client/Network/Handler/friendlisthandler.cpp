#include "friendlisthandler.h"
#include "qbytearraylistutility.h"
#include "Controller/clientcontroller.h"

friendListHandler::friendListHandler(QObject *parent)
    : MsgHandler{parent}
{}

void friendListHandler::parse(Msg &msg)
{
    QByteArray content = msg.getContent();
    QList<QByteArray> bytelist = QByteArrayListUtility::fromQByteArray(content);
    qDebug() << "[friendListHandler] parse 被调用啦，收到好友数量：" << bytelist.size();

    auto friendList = ClientController::getClientInstance()->getFriendList();
    auto chatMsgMap = ClientController::getClientInstance()->getChatMsgMap();
    friendList->clear();
    for (auto x : bytelist) {
        friendList->append(UserInfo::fromQByteArray(x));
    }
    chatMsgMap->clear();
    for (auto x : *friendList) {
        (*chatMsgMap)[x.getID()] = new QList<ChatMessage>;
    }
    emit sigFriendListGotcha(ClientController::getClientInstance()->getMyInfo());
}
