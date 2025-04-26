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
               "PRIMARY KEY (user_id, friend_id),"
               "FOREIGN KEY (user_id) REFERENCES UserInfo(Id),"
               "FOREIGN KEY (friend_id) REFERENCES UserInfo(Id))");
    query.exec("CREATE TABLE IF NOT EXISTS Message ("
               "Sender INTEGER,"
               "Receiver INTEGER,"
               "Content TEXT NOT NULL,"
               "Timestamp TIMESTAMP NOT NULL,"
               "FOREIGN KEY (Sender) REFERENCES UserInfo(Id),"
               "FOREIGN KEY (Receiver) REFERENCES UserInfo(Id))");
    query.exec("CREATE TABLE IF NOT EXISTS OfflineMessage ("
               "Sender INTEGER,"
               "Receiver INTEGER,"
               "Content TEXT NOT NULL,"
               "Timestamp TIMESTAMP NOT NULL,"
               "FOREIGN KEY (Sender) REFERENCES UserInfo(Id),"
               "FOREIGN KEY (Receiver) REFERENCES UserInfo(Id))");

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

    // 插入 ID1 -> ID2
    query.prepare("INSERT INTO Friendship (user_id, friend_id) VALUES(:Id1,:Id2)");
    query.bindValue(":Id1", QVariant(Id1));
    query.bindValue(":Id2", QVariant(Id2));
    if (!query.exec()) {
        Record::getRecord()->writeRecord("添加好友失败（正向）:" + query.lastError().text());
    } else {
        Record::getRecord()->writeRecord(QString("ID[%1]添加了ID[%2]为好友").arg(Id1).arg(Id2));
    }

    // 插入 ID2 -> ID1
    query.prepare("INSERT INTO Friendship (user_id, friend_id) VALUES(:Id1,:Id2)");
    query.bindValue(":Id1", QVariant(Id2));
    query.bindValue(":Id2", QVariant(Id1));
    if (!query.exec()) {
        Record::getRecord()->writeRecord("添加好友失败（反向）:" + query.lastError().text());
    } else {
        Record::getRecord()->writeRecord(QString("ID[%1]添加了ID[%2]为好友").arg(Id2).arg(Id1));
    }
}
//删除好友
void MySqlHelper::deleteFriendship(quint32 Id1, quint32 Id2) {
    QSqlQuery query;
    query.prepare("DELETE FROM Friendship "
                  "WHERE (user_id = :Id1 AND friend_id = :Id2) "
                  "   OR (user_id = :Id2 AND friend_id = :Id1)");
    query.bindValue(":Id1", QVariant(Id1));
    query.bindValue(":Id2", QVariant(Id2));

    if (!query.exec()) {
        Record::getRecord()->writeRecord("删除好友失败: " + query.lastError().text());
    } else {
        Record::getRecord()->writeRecord(QString("ID[%1]与ID[%2]取消好友关系！").arg(Id1).arg(Id2));
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
//好友关系是否存在
bool MySqlHelper::friendshipExist(quint32 Id1,quint32 Id2){
    QSqlQuery query;
    //向数据库发送一个预编译语句
    query.prepare("select * from Friendship where user_id =:Id1 and friend_id =:Id2");
    query.bindValue(":Id1", QVariant(Id1));
    query.bindValue(":Id2", QVariant(Id2));
    if (!query.exec()) {
        Record::getRecord()->writeRecord("好友关系查找失败:" + query.lastError().text());
        return false;
    }

    return query.next(); //如果有结果行，说明存在好友关系
}

//查询所有好友的信息，返回一个包含User Info的QList
QList<QByteArray> MySqlHelper::selectAllFriendsUserInfo(quint32 UserId) {
    QSqlQuery query;
    query.prepare("select Id,Username,Avatar from UserInfo where Id in (select friend_id from Friendship where user_id =:UserId)");
    query.bindValue(":UserId", QVariant(UserId));
    query.exec();
    QList<QByteArray> ListUserInfo;
    ListUserInfo.clear();
    while (query.next()) {
        ListUserInfo.append(UserInfo(query.value("Id").toInt(), query.value("Username").toString(),"",query.value("Avatar").toString()).toQByteArray());
    }
    return ListUserInfo;
}

void MySqlHelper::changeUsername(quint32 ID, QString Username)
{
    QSqlQuery query;
    query.prepare("UPDATE UserInfo SET Username = :Username WHERE ID = :ID");
    query.bindValue(":ID",QVariant(ID));
    query.bindValue(":Username",QVariant(Username));
    if (!query.exec()) {
        Record::getRecord()->writeRecord("修改昵称失败:" + query.lastError().text());
    } else {
        Record::getRecord()->writeRecord(QString("用户[%1]昵称已更新为[%2]").arg(ID).arg(Username));
    }
}

void MySqlHelper::changeAvatar(quint32 ID, QString Avatar)
{
    QSqlQuery query;
    query.prepare("UPDATE UserInfo SET Avatar = :Avatar WHERE ID = :ID");
    query.bindValue(":ID",QVariant(ID));
    query.bindValue(":Avatar",QVariant(Avatar));
    if (!query.exec()) {
        Record::getRecord()->writeRecord("修改头像失败:" + query.lastError().text());
    } else {
        Record::getRecord()->writeRecord(QString("用户[%1]头像路径已更新为[%2]").arg(ID).arg(Avatar));
    }
}

void MySqlHelper::addMsg(quint32 Sender, quint32 Receiver, QString Msg, QString Time)
{
    QSqlQuery query;
    query.prepare("insert into Message values(:Sender,:Receiver,:Msg,:Time)");
    query.bindValue(":Sender", QVariant(Sender));
    query.bindValue(":Receiver", QVariant(Receiver));
    query.bindValue(":Msg", Msg);
    query.bindValue(":Time", Time);
    if (!query.exec()) {
        Record::getRecord()->writeRecord("添加消息失败:" + query.lastError().text());
    } else {
        Record::getRecord()->writeRecord(QString("已添加消息[%1] -> [%2]：%3").arg(Sender)
                                             .arg(Receiver)
                                             .arg(Msg)
                                             .arg(Time)
                                         );
    }
}

void MySqlHelper::addOfflineMsg(ChatMessage &msg)
{
    QSqlQuery query;
    query.prepare("insert into OfflineMessage values(:Sender,:Receiver,:Msg,:Time)");
    query.bindValue(":Sender",QVariant(msg.getSender()));
    query.bindValue(":Receiver",QVariant(msg.getReceiver()));
    query.bindValue(":Msg",QVariant(msg.getContent()));
    query.bindValue(":Time",QVariant(msg.getTimeStamp()));
    if (!query.exec()) {
        Record::getRecord()->writeRecord("添加离线消息失败:" + query.lastError().text());
    } else {
        Record::getRecord()->writeRecord(QString("已添加离线消息[%1] -> [%2]：%3 （%4）")
                                             .arg(msg.getSender())
                                             .arg(msg.getReceiver())
                                             .arg(msg.getContent())
                                         .arg(msg.getTimeStamp())
                                         );
    }
}

QList<ChatMessage> MySqlHelper::getOfflineMsg(quint32 UserID)
{
    QList<ChatMessage> msg;
    msg.clear();

    QSqlQuery query;
    query.prepare("select * from OfflineMessage where Receiver = :UserID");
    query.bindValue(":UserID", QVariant(UserID));

    if (!query.exec()) {
        Record::getRecord()->writeRecord("查询离线消息失败: " + query.lastError().text());
        return msg; // 查询失败直接返回空列表
    }
    while (query.next()) {
        ChatMessage nowmsg(query.value("Sender").toUInt(),
                           query.value("Receiver").toUInt(),
                           query.value("Content").toString());
        nowmsg.setTimeStamp(query.value("Timestamp").toString());
        msg.append(nowmsg);
        Record::getRecord()->writeRecord(
            QString("读取离线消息：[%1] -> [%2]：%3 （%4）")
                .arg(nowmsg.getSender())
                .arg(nowmsg.getReceiver())
                .arg(nowmsg.getContent())
                .arg(nowmsg.getTimeStamp())
            );
    }
    return msg;
}

void MySqlHelper::deleteOfflineMsg(quint32 UserID)
{
    QSqlQuery query;
    query.prepare("delete from OfflineMessage where Receiver = :UserID");
    query.bindValue(":UserID",QVariant(UserID));
    query.exec();
}


