#ifndef CLIENTCONTROLLER_H
#define CLIENTCONTROLLER_H

#include <QObject>
#include <memory> //智能指针
#include "datamodel.h"
#include "Network/tcpclientsocket.h"

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

private:

    static ClientController* obj; //自己的实例

    //类内进行连接服务器
    //负责连接管理，并确保只创建一个TcpClientSocket实例
    static QString IP;
    void connectToServer();
    TcpClientSocket* getSocket();
    std::unique_ptr<TcpClientSocket> socket; // 用智能指针代替裸指针
};

#endif // CLIENTCONTROLLER_H
