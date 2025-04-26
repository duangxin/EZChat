#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "Utilities/stdDateTime.h"

#include "datamodel.h"

class DataBase
{
public:
    explicit DataBase();
    ~DataBase();
    //单例设计模式--应对数据库的对象的内存使用
    static DataBase* GetInstance();
    void addMsg(quint32 Sender, quint32 Receiver, QString Msg,
                QString Time = StdDateTime::GetDateTime());

    //加载聊天记录
    QVector<ChatMessage> loadChatHistory(quint32 myId, quint32 friendId);

    //同步聊天记录
    bool syncMessagesFromServer(const QByteArray& serverData);

private:
    QSqlDatabase sqldb;
    static DataBase* db;
};

#endif // DATABASE_H
