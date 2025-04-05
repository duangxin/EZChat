#ifndef USERINFO_H
#define USERINFO_H

#include <QObject>

class UserInfo
{
public:

    explicit UserInfo(quint32 id = 0x0000,
                      QString name = "",
                      QString pwd = "",
                      QString avatar_name = ""
                      );

    //getters,const让函数内部不能修改对象状态
    quint32 getID() const;
    QString getName() const;
    QString getPwd() const;
    QString getAvatarName() const;
/*
    UserInfo编码方式:
    |4:id|4:nameSize|name|4:pwdSize|pwd|4:avatarSize|avatar|
    说明:
    id      :4字节, quint32
    nameSize:4字节, quint32
    name    :nameSize字节,UTF-8字符串,用户名内容
    pwdSize :4字节, quint32
    pwd     :pwdSize字节，UTF-8字符串，密码内容
    avatarSize:4字节, quint32
    avatar  :avatarSize字节，UTF-8字符串，头像文件名内容
*/
    //从流中读取，或转为QByteArray可发送类型
    QByteArray toQByteArray();
    static UserInfo fromQByteArray(const QByteArray &data);

protected:
    quint32 m_id;
    QString m_name;
    QString m_pwd;
    QString m_avatar_name;

};

#endif // USERINFO_H
