#ifndef CLIENTCONTROLLER_H
#define CLIENTCONTROLLER_H

#include <QObject>
#include <memory> //智能指针
#include "datamodel.h"
#include "Network/tcpclientsocket.h"
#include "Network/clienthandlerreg.h"

class ClientController  : public QObject
{
    Q_OBJECT
public:
    explicit ClientController(QObject* parent = nullptr);
    //~ClientController();    //要析构一些非 QObject 类型的成员变量
    //单例
    static ClientController* getClientInstance();
    //注册登录
    void requestRegister(QString username, QString password);
    void requestLogin(quint32 id, QString password);
    void requestLogout(quint32 id);
    UserInfo& getMyInfo();

    //好友请求
    void requestAddFriend(quint32 receiver);
    void agreeFriendRequest(quint32 sender, quint32 receiver);
    void declineFriendRequest(quint32 sender, quint32 receiver);
    void requestDeleteFriend(quint32 receiver);
    QList<UserInfo> *getFriendList();   //给UI展示好友列表
    void dynamicAppendFriend(UserInfo _friend); //新好友，更新列表
    void dynamicRemoveFriend(UserInfo _friend);


    //修改信息
    void requestModifyUserName(QString newUserName);
    void requestModifyAvatar(QString imgPath);

    //向服务器获取好友列表
    void requestFriendList(UserInfo info);
    friend class friendListHandler;

    //发送聊天消息
    void sendChatMessage(quint32 receiver, QString content);
    QList<ChatMessage> *getChatMsg(quint32 id);

    //向服务器获取聊天记录
    void requestSyncMessages();

private slots:



private:


    QMap<quint32, QList<ChatMessage>*>* getChatMsgMap() { return &chatMsgMap; }
    QMap<quint32, QList<ChatMessage>*> chatMsgMap;
        //好友列表
    QList<UserInfo> friendList;

    static ClientController* obj; //自己的实例

    //类内进行连接服务器
    //负责连接管理，并确保只创建一个TcpClientSocket实例
    //static QString IP; 定义宏了
    void connectToServer();
    TcpClientSocket* getSocket();
    std::unique_ptr<TcpClientSocket> socket; // 用智能指针代替裸指针
    void sendMessageWhenConnected(std::unique_ptr<Msg> msg);
};

#endif // CLIENTCONTROLLER_H
