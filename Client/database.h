#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "datamodel.h"

class DataBase
{
public:
    explicit DataBase();
    ~DataBase();
    //单例设计模式--应对数据库的对象的内存使用
    static DataBase* GetInstance();
    //注册
    void registerUserInfo(const UserInfo& user);

private:
    QSqlDatabase sqldb;
    static DataBase* db;
};

#endif // DATABASE_H
