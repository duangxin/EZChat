#ifndef SERVERCONTROLLER_H
#define SERVERCONTROLLER_H
#include "Network/server.h"

//和clientController差不多，专门用来单例一个server
class ServerController : public QObject
{
    Q_OBJECT
public:
    explicit ServerController();

    //单例
    static ServerController* getCtrlInstance();

    static Server* getServerInstance();
    void sendMessageWhenConnected(TcpClientSocket *socket, std::unique_ptr<Msg> msg);
private:
    static Server* m_server;
    static ServerController* obj; //自己的实例
};

#endif // SERVERCONTROLLER_H
