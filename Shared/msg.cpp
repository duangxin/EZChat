#include "msg.h"
#include <QIODevice>
#include <QDebug>

Msg::Msg(MsgType type, const QByteArray & content){
    this->m_type = type;
    this->m_content = content;
}

QByteArray Msg::toQByteArray()
{
    //|4:contentSize|2:type|?:content|
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_6_7);

    //stream<<QByteArray 会自动存储数据大小,多余数据
    //writeRawData() 只写入原始数据，不存储数据的大小（写入的数据，数据长度）

    stream << static_cast<quint32>(m_content.size())
           << static_cast<quint16>(m_type);

    stream.writeRawData(m_content.constData(), m_content.size());

    return data;
}

Msg Msg::fromQByteArray(const QByteArray &data)
{
    //|4:contentSize|2:type|?:content|
    QDataStream stream(data);
    stream.setVersion(QDataStream::Qt_6_7);

    quint32 contentSize;
    quint16 type;
    QByteArray content;

    //将数据从type_and_content中拿出来
    stream >> contentSize;
    //假如数据不完整, 停止读取
    if(data.size() - sizeof(quint32) - sizeof(quint16)< contentSize){
         qDebug() <<data.size();
        qDebug() <<contentSize;
         qDebug() <<"信息接收不全";
        return Msg(MsgType::UNDEFINED, QByteArray() );
    }
    //继续读取
    stream >> type;
    content.resize(contentSize);
    stream.readRawData(content.data(), contentSize);
    return Msg((MsgType)(type),content);
}

MsgType Msg::getType()
{
    return m_type;
}

QByteArray &Msg::getContent()
{
    return m_content;
}
