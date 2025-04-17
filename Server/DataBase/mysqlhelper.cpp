#include "mysqlhelper.h"
#include "Utilities/record.h"

MySqlHelper * MySqlHelper::sqlObj = nullptr;
MySqlHelper::MySqlHelper() {}

MySqlHelper::~MySqlHelper()
{
    if (sqlObj != nullptr) {
        delete sqlObj;
    }
}

MySqlHelper *MySqlHelper::GetInstance()
{
    if(!sqlObj){
        sqlObj = new MySqlHelper();
    }
    return sqlObj;
}

bool MySqlHelper::connect(const QString &host, const QString &dbName, const QString &user, const QString &password)
{
    mysql_db = QSqlDatabase::addDatabase("QMYSQL");
    mysql_db.setPort(3306);
    mysql_db.setHostName(host);
    mysql_db.setDatabaseName(dbName);
    mysql_db.setUserName(user);
    mysql_db.setPassword(password);
    if (!mysql_db.open()) {
        Record::getRecord()->writeRecord("服务器MySQL连接失败:" + mysql_db.lastError().text());
        return false;
    }
    Record::getRecord()->writeRecord("服务器MySQL连接成功");
    return true;

}

void MySqlHelper::initTables()
{
    //初始化建表
    QSqlQuery query;
    //用户表(ID，用户名，密码，头像，最后一次同步
    query.exec("CREATE TABLE IF NOT EXISTS UserInfo ("
               "Id INTEGER PRIMARY KEY,"
               "Username VARCHAR(40) NOT NULL,"
               "Pwd VARCHAR(128) NOT NULL,"
               "Avatar VARCHAR(512),"
               "last_sync TIMESTAMP DEFAULT CURRENT_TIMESTAMP)");
    //好友关系表(
    query.exec("CREATE TABLE IF NOT EXISTS Friendship ("
               "user_id INTEGER, "
               "friend_id INTEGER, "
               "FOREIGN KEY (user_id) REFERENCES UserInfo(Id),"
               "FOREIGN KEY (friend_id) REFERENCES UserInfo(Id))");
    Record::getRecord()->writeRecord("MySql表初始化完成");
}

quint32 MySqlHelper::generateUserId()
{
    QSet<quint32> existingIds;
    QSqlQuery query;
    quint32 newId;

    // 查询所有已有的Id
    if (query.exec("SELECT Id FROM UserInfo")) {
        while (query.next()) {
            existingIds.insert(query.value(0).toUInt());    //存在的插入set中
        }
    }else {
        Record::getRecord()->writeRecord("查询数据库失败: " + query.lastError().text());
        return 0;
    }

    while (true) {
        newId = QRandomGenerator::global()->bounded(100000, 1000000);
        if (!existingIds.contains(newId)) {
            Record::getRecord()->writeRecord("[分配ID]： " + QString::number(newId));
            return newId;
        }
    }
}

void MySqlHelper::addUser(const UserInfo &user)
{
    QSqlQuery query;
    query.prepare("INSERT INTO UserInfo (Id, Username, Pwd, Avatar) "
                  "VALUES (:Id, :Username, :pwd, :avatar)");
    query.bindValue(":Id", user.getID());
    query.bindValue(":Username", user.getName());
    query.bindValue(":pwd", user.getPwd());
    query.bindValue(":avatar", user.getAvatarName());
    if (!query.exec()) {
        Record::getRecord()->writeRecord("插入数据库失败:" + query.lastError().text());
    } else {
        Record::getRecord()->writeRecord(QString("ID[%1]插入数据库成功！").arg(user.getID()));
    }
}

//添加好友 添加双向
void MySqlHelper::addFriendship(quint32 Id1, quint32 Id2) {
    QSqlQuery query;
    query.prepare("insert into Friendship values(:Id1,:Id2)");
    query.bindValue(":Id1", QVariant(Id1));
    query.bindValue(":Id2", QVariant(Id2));
    if (!query.exec()) {
        Record::getRecord()->writeRecord("添加好友失败:" + query.lastError().text());
    } else {
        Record::getRecord()->writeRecord(QString("ID[%1]与ID[%2]成为好友！").arg(Id1).arg(Id2));
    }
}

//登录验证
bool MySqlHelper::loginCheck(const quint32 Id, const QString pwd) {
    QSqlQuery query;
    //向数据库发送一个预编译语句
    query.prepare("select * from UserInfo where Id =:Id and pwd =:pwd");
    query.bindValue(":Id", QVariant(Id));
    query.bindValue(":pwd", QVariant(pwd));
    if (!query.exec()) {
        Record::getRecord()->writeRecord("用户查找失败:" + query.lastError().text());
    }
    if (query.next()) {
        Record::getRecord()->writeRecord(QString("已找到有效用户[%1]！").arg(Id));
        return query.value(0).toInt() > 0;
    }
    Record::getRecord()->writeRecord(QString("未找到用户[%1]或密码错误").arg(Id));
    return false;
}

//返回用户信息
UserInfo MySqlHelper::selectUserInfoById(const quint32 id){
    QSqlQuery query;
    query.prepare("select * from UserInfo where Id =:Id");
    query.bindValue(":Id", QVariant(id));
    query.exec();
    UserInfo tmp;
    while(query.next()){
        tmp = UserInfo(query.value("Id").toUInt(),
                       query.value("Username").toString(),
                       "",
                       query.value("Avatar").toString()
                       );
    }
    return tmp;
}
