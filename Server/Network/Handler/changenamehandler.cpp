#include "changenamehandler.h"

changeNameHandler::changeNameHandler(QObject *parent)
    : MsgHandler{parent}
{}

void changeNameHandler::parse(Msg &msg, TcpClientSocket *socket)
{
    Record::getRecord()->writeRecord("[修改昵称请求]尝试解析...");
    if (msg.getType() != MsgType::MODIFY_USERNAME) {
        Record::getRecord()->writeRecord("修改昵称Msg错误！");
        return;
    }
    //把接收到的Msg转换成UserInfo对象
    UserInfo tmp = UserInfo::fromQByteArray(msg.getContent());
    auto dbHelper = MySqlHelper::GetInstance();

    dbHelper->changeUsername(tmp.getID(),tmp.getName());
    Record::getRecord()->writeRecord("[修改昵称请求]修改成功！");
    auto replyMsg = std::make_unique<Msg>(MsgType::MODIFY_USERNAME_SUCCESS,tmp.toQByteArray());
    ServerController::getCtrlInstance()->sendMessageWhenConnected(socket,std::move(replyMsg));
}
