#ifndef CHATMESSAGE_H
#define CHATMESSAGE_H

#include <QObject>

//聊天信息类, 一条信息就是一个该类的instance
class ChatMessage
{

public:
    ChatMessage(){}
    explicit ChatMessage(quint32 sender, quint32 receiver, const QString& content="");
    //getters
    quint32 getSender() const;
    quint32 getReceiver() const;
    const QString& getContent() const; // 返回只读引用 + const成员函数
    const QString& getTimeStamp() const; //获得消息的时间戳

    void setSender(quint32 sender);
    void setReceiver(quint32 receiver);
    void setContent(const QString &content);
    void setTimeStamp(const QString& timestamp);
    //转换函数, 便于丢给Msg后再发送
    //对于ChatMessage的QByteArray编码方式
    // | quint32 sender | quint32 receiver |  quint32 time_stamp size | time_stamp | quint32 content size | content |

    static ChatMessage fromQByteArray(QByteArray chat_msg);
    QByteArray toQByteArray();



signals:

private:
    //friend class MySqlHelper;
    quint32 _sender;
    quint32 _receiver;
    QString _time_stamp; //时间戳在构造函数中创建
    QString _content;

};

#endif // CHATMESSAGE_H
