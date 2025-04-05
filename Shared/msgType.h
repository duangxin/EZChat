#ifndef MSGTYPE_H
#define MSGTYPE_H

#include <QObject>

/*

    消息的类型    没有明确赋值，它们会自动递增1

0x0000 - 0x001F     通用消息(未定义、文本、图片等)
0x0020 - 0x003F     登录、注册相关
0x0040 - 0x005F     好友管理相关
0x0060 - 0x007F     群聊相关
0x0080 - 0x009F     在线状态
0x00A0 - 0x00BF     个人信息
0x0100 - 0x011F     群组管理
0x0120 - 0x013F     账户修改(用户名、头像等)
0x0140 - 0x015F     资源文件(图片、文件)
0x0160 - 0xFFFF     预留给新功能

*/


enum class MsgType : quint16 {

    //客户端处理的消息
    UNDEFINED = 0x0000,MSG_TEXT, MSG_PIC, MSG_EMOTION,

    //注册 登录 重置密码请求
    REQUEST_REGISTER = 0x0020, REQUEST_LOGIN, REQUEST_LOGOUT,REQUEST_RESETPSW,

    //服务器向客户端返回的内容
    REGISTER_SUCCESS = 0x0030, REGISTER_ERROR, //注册成功/失败
    LOGIN_SUCCESS, LOGIN_ERROR, //登录成功/失败
    LOGOUT_SUCCESS, LOGOUT_ERROR,
    RESETPW_SUCCESS, RESETPW_ERROR, //重置密码成功/失败


};

#endif // MSGTYPE_H
