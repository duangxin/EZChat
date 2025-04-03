#include "userinfo.h"

UserInfo::UserInfo(quint32 id,
                   QString name,
                   QString pwd,
                   QString avatar_name
                   ): m_id(id), m_name(name), m_pwd(pwd), m_avatar_name(avatar_name)
{

}


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
