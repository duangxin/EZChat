#include "syncmessageshandler.h"

syncMessagesHandler::syncMessagesHandler(QObject *parent)
    : MsgHandler{parent}
{}

void syncMessagesHandler::parse(Msg &msg, TcpClientSocket *socket)
{
        Record::getRecord()->writeRecord("[聊天记录同步请求]尝试解析...");
    if (msg.getType() != MsgType::REQUEST_SYNC_MESSAGES) {
        qDebug() << "[聊天记录同步请求]收到错误的消息类型！";
        return;
    }
    auto dbHelper = MySqlHelper::GetInstance();
    QSqlQuery query("SELECT Sender, Receiver, Content, Timestamp FROM Message");

    QJsonArray messageArray;
    while (query.next()) {
        QJsonObject obj;
        obj["Sender"] = query.value(0).toInt();
        obj["Receiver"] = query.value(1).toInt();
        obj["Content"] = query.value(2).toString();
        obj["Timestamp"] = query.value(3).toString();
        messageArray.append(obj);
    }

    QJsonDocument doc(messageArray);
    QByteArray content = doc.toJson(QJsonDocument::Compact);

    auto replyMsg = std::make_unique<Msg>(MsgType::RETURN_SYNC_MESSAGES, content);
    ServerController::getCtrlInstance()->sendMessageWhenConnected(socket, std::move(replyMsg));

    Record::getRecord()->writeRecord("[聊天记录同步请求]聊天记录发送完毕，总数：" + QString::number(messageArray.size()));

}
