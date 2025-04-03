#include "database.h"
#include <QMessageBox>


//静态成员变量的类外初始化
DataBase* DataBase::db = NULL;
DataBase::DataBase() {
    sqldb = QSqlDatabase::addDatabase("QSQLITE");
    sqldb.setDatabaseName("chat_client.db");
    if (!sqldb.open()) {
        QMessageBox::warning(NULL, "错误", "打开数据库时出现错误!", QMessageBox::Yes);
    }

    //初始化建表
    QSqlQuery query;
    //用户表(ID，用户名，密码，头像，最后一次同步
    query.exec("CREATE TABLE UserInfo ("
               "Id INTEGER PRIMARY KEY,"
               "Username VARCHAR(40) NOT NULL,"
               "Pwd VARCHAR(40) NOT NULL,"
               "Avatar VARCHAR(512),"
               "last_sync TIMESTAMP))");
    //好友关系表(
    query.exec("CREATE TABLE Friendship ("
               "user_id INTEGER, "
               "friend_id INTEGER, "
               "FOREIGN KEY (user_id) REFERENCES UserInfo(Id),"
               "FOREIGN KEY (friend_id) REFERENCES UserInfo(Id))");
}


DataBase::~DataBase() {
    if (db != NULL) {
        delete db;
    }
}
DataBase* DataBase::GetInstance() {
    if (db == NULL) {
        db = new DataBase;
    }
    return db;
}

//注册信息
void DataBase::registerUserInfo(const UserInfo& user) {
    QSqlQuery query;
    query.prepare("insert into UserInfo values(:Id,:Username,:pwd,:avatar)");
    query.bindValue(":Id", user.getID());
    query.bindValue(":Username", user.getName());
    query.bindValue(":pwd", user.getPwd());
    query.bindValue(":avatar", user.getAvatarName());
    query.exec();
}
