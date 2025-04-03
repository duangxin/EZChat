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

    protected:
        quint32 m_id;
        QString m_name;
        QString m_pwd;
        QString m_avatar_name;

};

#endif // USERINFO_H
