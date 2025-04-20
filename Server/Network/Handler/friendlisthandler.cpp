#include "friendlisthandler.h"
#include "qbytearraylistutility.h"

friendListHandler::friendListHandler(QObject *parent)
    : MsgHandler{parent}
{}

void friendListHandler::parse(Msg &msg, TcpClientSocket *socket)
{
    Record::getRecord()->writeRecord("[获取好友列表请求]尝试解析...");
    if (msg.getType() != MsgType::REQUEST_ALL_FRIEND_LIST) {
        Record::getRecord()->writeRecord("获取好友列表请求Msg错误！");
        return;
    }

    UserInfo tmp = UserInfo::fromQByteArray(msg.getContent());
    auto dbHelper = MySqlHelper::GetInstance();
    QList<QByteArray> list = dbHelper->selectAllFriendsUserInfo(tmp.getID());
    QByteArray content = QByteArrayListUtility::toQByteArray(list);
    qDebug() << "[getFriendInfo] 获取好友数量：" << list.size();
    Record::getRecord()->writeRecord("[获取好友列表请求]获取成功");
    auto replyMsg = std::make_unique<Msg>(MsgType::ALL_FRIEND_LIST,content);
    ServerController::getCtrlInstance()->sendMessageWhenConnected(socket,std::move(replyMsg));
}
