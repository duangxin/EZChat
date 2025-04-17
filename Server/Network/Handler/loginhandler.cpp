#include "loginhandler.h"
#include "Utilities/record.h"
#include "DataBase/mysqlhelper.h"
#include "../../Controller/servercontroller.h"

loginHandler::loginHandler(QObject *parent)
    : MsgHandler{parent}
{}

void loginHandler::parse(Msg &msg, TcpClientSocket *socket)
{
    Record::getRecord()->writeRecord("[登录请求]尝试解析...");
    if (msg.getType() != MsgType::REQUEST_LOGIN) {
        Record::getRecord()->writeRecord("登录Msg错误！");
        return;
    }
    //把接收到的Msg转换成UserInfo对象
    UserInfo tmp = UserInfo::fromQByteArray(msg.getContent());
    auto dbHelper = MySqlHelper::GetInstance();

    bool canLogin = dbHelper->loginCheck(tmp.getID(),tmp.getPwd());
    MsgType type = canLogin ? MsgType::LOGIN_SUCCESS : MsgType::LOGIN_ERROR;

    if(canLogin){
        //如果登录成功了再将某客户端对应的socket添加到Server中.
        ServerController::getServerInstance()->addClient(tmp.getID(), socket);
        Record::getRecord()->writeRecord("[登录请求]用户[" + QString::number(tmp.getID()) + "]登陆成功!");
        //并且还要返回用户的其他信息, 比如用户名和头像
        UserInfo all_userinfo = dbHelper->selectUserInfoById(tmp.getID());
        tmp = UserInfo(all_userinfo.getID(),all_userinfo.getName(),tmp.getPwd(),all_userinfo.getAvatarName());
    }else{
        Record::getRecord()->writeRecord("[登录请求]用户[" + QString::number(tmp.getID()) + "]登录失败!");
    }

    auto replyMsg = std::make_unique<Msg>(type, tmp.toQByteArray());
    ServerController::getCtrlInstance()->sendMessageWhenConnected(socket,std::move(replyMsg));
}
