#include "registerhandler.h"

registerHandler::registerHandler(QObject *parent)
    : MsgHandler{parent}
{}

void registerHandler::parse(Msg &msg, TcpClientSocket *socket)
{
    Record::getRecord()->writeRecord("[注册请求]尝试解析...");
    if (msg.getType() != MsgType::REQUEST_REGISTER) {
        Record::getRecord()->writeRecord("注册Msg错误！");
        return;
    }
    //把接收到的Msg转换成UserInfo对象
    UserInfo tmp = UserInfo::fromQByteArray(msg.getContent());
    auto dbHelper = MySqlHelper::GetInstance();
    //给用户分配一个ID
    tmp.setID(dbHelper->generateUserId());
    //插入到数据库里面
    dbHelper->addUser(tmp);
    dbHelper->addFriendship(tmp.getID(), tmp.getID());

    Record::getRecord()->writeRecord(QString("[注册请求]用户[%1]注册成功，分配ID[%2]").arg(tmp.getName()).arg(tmp.getID()));
    auto replyMsg = std::make_unique<Msg>(MsgType::REGISTER_SUCCESS, tmp.toQByteArray());

    ServerController::getCtrlInstance()->sendMessageWhenConnected(socket,std::move(replyMsg));

}
