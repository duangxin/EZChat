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
    UserInfo& getMyInfo();

    //好友请求
    void requestAddFriend(quint32 receiver);
    void agreeFriendRequest(quint32 sender, quint32 receiver);
    void declineFriendRequest(quint32 sender, quint32 receiver);
    QList<UserInfo> *getFriendList();   //给UI展示好友列表
    void dynamicAppendFriend(UserInfo _friend); //新好友，更新列表

    friend class friendListHandler;

private slots:

    void requestFriendList(UserInfo info);//向服务器获取好友列表

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
