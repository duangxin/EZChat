#include "changeavatarhandler.h"

changeAvatarHandler::changeAvatarHandler(QObject *parent)
    : MsgHandler{parent}
{}

void changeAvatarHandler::parse(Msg &msg, TcpClientSocket *socket)
{
    Record::getRecord()->writeRecord("[修改头像请求]尝试解析...");
    if (msg.getType() != MsgType::MODIFY_AVATAR) {
        Record::getRecord()->writeRecord("修改头像Msg错误！");
        return;
    }
    //把接收到的Msg转换成UserInfo对象
    UserInfo tmp = UserInfo::fromQByteArray(msg.getContent());
    auto dbHelper = MySqlHelper::GetInstance();

    dbHelper->changeAvatar(tmp.getID(),tmp.getAvatarName());
    Record::getRecord()->writeRecord("[修改头像请求]修改成功！");
    auto replyMsg = std::make_unique<Msg>(MsgType::MODIFY_AVATAR_SUCCESS,tmp.toQByteArray());
    ServerController::getCtrlInstance()->sendMessageWhenConnected(socket,std::move(replyMsg));
}
