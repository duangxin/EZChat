#include "chatmessage.h"
#include "Utilities/stdDateTime.h"

#include <QtNetwork>

//构造函数
ChatMessage::ChatMessage(quint32 sender, quint32 receiver, const QString& content) :
    _sender(sender),_receiver(receiver), _content(content)
{
    _time_stamp = StdDateTime::GetDateTime();
}

//getters
quint32 ChatMessage::getSender() const{
    return _sender;
}

quint32 ChatMessage::getReceiver() const{
    return _receiver;
}

const QString & ChatMessage::getContent() const{
    return _content;
}

const QString& ChatMessage::getTimeStamp() const {
    return _time_stamp;
}

void ChatMessage::setSender(quint32 sender) {
    _sender = sender;
}

void ChatMessage::setReceiver(quint32 receiver) {
    _receiver = receiver;
}

void ChatMessage::setContent(const QString& content) {
    _content = content;
}

void ChatMessage::setTimeStamp(const QString& timestamp) {
    _time_stamp = timestamp;
}



ChatMessage ChatMessage::fromQByteArray(QByteArray chat_msg){
    QDataStream in(chat_msg);
    in.setVersion(QDataStream::Qt_6_7);
    ChatMessage recvChatMsg(0,0,"");
    //写入发送者 接收者
    in >> recvChatMsg._sender;
    in >> recvChatMsg._receiver;
    //写入时间戳
    quint32 tmpSize;
    in >> tmpSize;
    QByteArray tmpTimeBlock;
    tmpTimeBlock.resize(tmpSize);
    in >> tmpTimeBlock;
    recvChatMsg._time_stamp = QString(tmpTimeBlock);
    //写入内容
    in >> tmpSize;
    QByteArray tmpContentBlock;
    tmpContentBlock.resize(tmpSize);
    in >> tmpContentBlock;
    recvChatMsg._content = QString(tmpContentBlock);

    return recvChatMsg;
}


QByteArray ChatMessage::toQByteArray(){
    QByteArray block;

    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << quint32(_sender);
    out << quint32(_receiver);
    //输出时间戳
    out << quint32(0);//预留给时间戳大小
    out << _time_stamp.toUtf8();
    out.device()->seek(8);
    out << (quint32)(block.size()-sizeof(quint32)*3);
    out.device()->seek(block.size());
    //输出内容
    QByteArray tmp = _content.toUtf8();
    out << quint32(sizeof(tmp));
    out << tmp;

    return block;
}
