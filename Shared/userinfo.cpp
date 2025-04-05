#include "userinfo.h"
#include <QIODevice>


UserInfo::UserInfo(quint32 id,QString name,QString pwd,QString avatar_name)
    : m_id(id), m_name(name), m_pwd(pwd), m_avatar_name(avatar_name)
{}


quint32 UserInfo::getID() const{
    return m_id;
}

QString UserInfo::getName() const{
    return m_name;
}

QString UserInfo::getPwd() const{
    return m_pwd;
}

QString UserInfo::getAvatarName() const{
    return m_avatar_name;
}



QByteArray UserInfo::toQByteArray()
{
    //  |4:id|4:nameSize|name|4:pwdSize|pwd|4:avatarSize|avatar|
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_6_0);
    //id
    stream << m_id;

    //stream<<QByteArray 会自动存储数据大小,多余数据
    //writeRawData() 只写入原始数据，不存储数据的大小

    //name
    QByteArray nameBytes =  m_name.toUtf8();
    stream << static_cast<quint32>(nameBytes.size()); // static_cast<quint32>用来显式数据转换，
    stream.writeRawData(nameBytes.constData(), nameBytes.size());//（写入的数据，数据长度）

    //pwd
    QByteArray pwdBytes =  m_pwd.toUtf8();
    stream << static_cast<quint32>(pwdBytes.size());
    stream.writeRawData(pwdBytes.constData(), pwdBytes.size());

    //avatar
    QByteArray avatarBytes =  m_avatar_name.toUtf8();
    stream << static_cast<quint32>(avatarBytes.size());
    stream.writeRawData(avatarBytes.constData(), avatarBytes.size());

    return data;
}

UserInfo UserInfo::fromQByteArray(const QByteArray &data)
{
    //  |4:id|4:nameSize|name|4:pwdSize|pwd|4:avatarSize|avatar|
    UserInfo tmp;
    QDataStream stream(data);
    stream.setVersion(QDataStream::Qt_6_0);

    quint32 nameSize, pwdSize, avatarSize;
    QByteArray nameBytes, pwdBytes, avatarBytes;

    //read id
    stream >> tmp.m_id;

    //read name
    stream >> nameSize; //读取四字节
    nameBytes.resize(nameSize); //设置name大小
    stream.readRawData(nameBytes.data(), nameSize); //读取name数据
    tmp.m_name = QString::fromUtf8(nameBytes);     //赋值给m_name

    //read pwd
    stream >> pwdSize;
    pwdBytes.resize(pwdSize);
    stream.readRawData(pwdBytes.data(), pwdSize);
    tmp.m_pwd = QString::fromUtf8(pwdBytes);

    //read avatar
    stream >> avatarSize;
    avatarBytes.resize(avatarSize);
    stream.readRawData(avatarBytes.data(), avatarSize);
    tmp.m_avatar_name = QString::fromUtf8(avatarBytes);

    return tmp;
}
