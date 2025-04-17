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
    //添加好友
    void addFriendship(quint32 Id1, quint32 Id2);
    //登录验证
    bool loginCheck(const quint32 Id, const QString pwd);
    //返回不包含密码的用户信息
    UserInfo selectUserInfoById(const quint32 id);
private:
    QSqlDatabase mysql_db;
    static MySqlHelper* sqlObj;
};

#endif // MYSQLHELPER_H

