#include "database.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

//静态成员变量的类外初始化
DataBase* DataBase::db = nullptr;
DataBase::DataBase() {
    sqldb = QSqlDatabase::addDatabase("QSQLITE");
    sqldb.setDatabaseName("chat_client.db");
    if (!sqldb.open()) {
        QMessageBox::warning(nullptr, "错误", "打开数据库时出现错误: " + sqldb.lastError().text(), QMessageBox::Yes);
        return;
    }
    QSqlQuery query(sqldb);
    QString createTable = "CREATE TABLE IF NOT EXISTS local_message ("
                          "Sender INTEGER, "
                          "Receiver INTEGER, "
                          "Content TEXT NOT NULL, "
                          "Timestamp DATETIME NOT NULL, "
                          "is_synced INTEGER DEFAULT 0)";
    if (!query.exec(createTable)) {
        QMessageBox::warning(nullptr, "数据库错误", "创建本地消息表失败: " + query.lastError().text(), QMessageBox::Yes);
    }
}


DataBase::~DataBase() {
    if (sqldb.isOpen()) {
        sqldb.close();
    }
}
DataBase* DataBase::GetInstance() {
    if (db == NULL) {
        db = new DataBase;
    }
    return db;
}

void DataBase::addMsg(quint32 Sender, quint32 Receiver, QString Msg, QString Time)
{
    if (!sqldb.isOpen()) {
        qDebug() << "数据库未打开，无法插入消息";
        return;
    }

    QSqlQuery query(sqldb);
    query.prepare("INSERT INTO local_message (Sender, Receiver, Content, Timestamp, is_synced) "
                  "VALUES (?, ?, ?, ?, 0)");
    query.addBindValue(Sender);
    query.addBindValue(Receiver);
    query.addBindValue(Msg);
    query.addBindValue(Time);

    if (!query.exec()) {
        qDebug() << "插入消息失败:" << query.lastError().text();
    }
}

QVector<ChatMessage> DataBase::loadChatHistory(quint32 myId, quint32 friendId)
{
    QVector<ChatMessage> history;

    if (!sqldb.isOpen()) {
        qDebug() << "数据库未打开，无法加载聊天记录";
        return history;
    }

    QSqlQuery query(sqldb);
    query.prepare("SELECT Sender, Receiver, Content, Timestamp "
                  "FROM local_message "
                  "WHERE (Sender = ? AND Receiver = ?) OR (Sender = ? AND Receiver = ?) "
                  "ORDER BY Timestamp ASC");
    query.addBindValue(myId);
    query.addBindValue(friendId);
    query.addBindValue(friendId);
    query.addBindValue(myId);

    if (!query.exec()) {
        qDebug() << "加载聊天记录失败:" << query.lastError().text();
        return history;
    }

    while (query.next()) {
        ChatMessage msg;
        msg.setSender(query.value(0).toUInt()) ;
        msg.setReceiver(query.value(1).toUInt());
        msg.setContent(query.value(2).toString());
        msg.setTimeStamp(query.value(3).toString());

        history.append(msg);
    }

    return history;
}

bool DataBase::syncMessagesFromServer(const QByteArray &serverData)
{
    if (!sqldb.isOpen()) {
        qDebug() << "数据库未打开，无法同步消息";
        return false;
    }

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(serverData, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << "同步消息解析失败:" << parseError.errorString();
        return false;
    }
    if (!doc.isArray()) {
        qDebug() << "服务器返回的数据格式错误（应该是数组）";
        return false;
    }
    QJsonArray messageArray = doc.array();
    QSqlQuery query(sqldb);
    // 清空原来的本地聊天记录
    if (!query.exec("DELETE FROM local_message")) {
        qDebug() << "清空旧聊天记录失败:" << query.lastError().text();
        return false;
    }
    query.prepare("INSERT INTO local_message (Sender, Receiver, Content, Timestamp, is_synced) "
                  "VALUES (?, ?, ?, ?, 1)");
    if (!sqldb.transaction()) {
        qDebug() << "开启事务失败:" << sqldb.lastError().text();
        return false;
    }
    for (const QJsonValue& value : messageArray) {
        QJsonObject obj = value.toObject();
        query.addBindValue(obj["Sender"].toInt());
        query.addBindValue(obj["Receiver"].toInt());
        query.addBindValue(obj["Content"].toString());
        query.addBindValue(obj["Timestamp"].toString());
        if (!query.exec()) {
            qDebug() << "插入同步消息失败:" << query.lastError().text();
            sqldb.rollback();
            return false;
        }
    }
    if (!sqldb.commit()) {
        qDebug() << "提交事务失败:" << sqldb.lastError().text();
        return false;
    }
    qDebug() << "聊天记录同步成功，总数:" << messageArray.size();
    return true;
}

