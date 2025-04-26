#ifndef MYSQLHELPER_H
#define MYSQLHELPER_H

#include <QtSql>
#include "datamodel.h"

class MySqlHelper
{
public:
    MySqlHelper();
    ~MySqlHelper();
    //单例设计模式--应对数据库的对象的内存使用
    static MySqlHelper* GetInstance();
    bool connect(const QString& host, const QString& dbName, const QString& user, const QString& password);
    void initTables();

    //给用户分配ID
    quint32 generateUserId();
    //注册
    void addUser(const UserInfo& user);
    //添加，删除好友
    void addFriendship(quint32 Id1, quint32 Id2);
    void deleteFriendship(quint32 Id1, quint32 Id2);
    //登录验证
    bool loginCheck(const quint32 Id, const QString pwd);
    //返回不包含密码的用户信息
    UserInfo selectUserInfoById(const quint32 id);
    //好友关系是否存在
    bool friendshipExist(quint32 Id1, quint32 Id2);
    //返回好友表
    QList<QByteArray> selectAllFriendsUserInfo(quint32 UserId);
    //改用户名，头像
    void changeUsername(quint32 ID,QString Username);
    void changeAvatar(quint32 ID,QString Avatar);
    //添加消息
    void addMsg(quint32 Sender,quint32 Receiver,QString Msg,QString Time);

    //离线消息，添加获取删除
    void addOfflineMsg(ChatMessage &msg);
    QList<ChatMessage> getOfflineMsg(quint32 UserID);
    void deleteOfflineMsg(quint32 UserID);


private:
    QSqlDatabase mysql_db;
    static MySqlHelper* sqlObj;
};

#endif // MYSQLHELPER_H

