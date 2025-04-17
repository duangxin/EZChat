#ifndef MSG_H
#define MSG_H

#include <QObject>
#include "msgType.h"

//服务端和客户端仅通过message通信

/*

使用 QByteArray进行数据封装，自定义MSG格式:
    |4:contentSize|2:type|?:content|
    说明:
    contentSize: 占 4 个字节, quint32, 整个数据包的大小（仅包含 content）
    type    : 占 2 个字节, quint16, 用于标识数据包类型
    content : 占未定字节 , 数据包的具体内容, 取决于type, 由handler解析

 */

class Msg
{
public:
    Msg(MsgType type, const QByteArray & content);

    //转为QByteArray可发送类型
    QByteArray toQByteArray();
    //从流中读取,转为message
    static Msg fromQByteArray(const QByteArray &data);
    //给Handler提供直接操作Msg的接口
    MsgType getType();
    QByteArray & getContent();

private:
    //quint32 m_contentSize;
    MsgType m_type;
    QByteArray m_content;
};

#endif // MSG_H
