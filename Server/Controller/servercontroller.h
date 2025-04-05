#ifndef SERVERCONTROLLER_H
#define SERVERCONTROLLER_H
#include "Network/server.h"

//和clientController差不多，专门用来单例一个server
class ServerController : public QObject
{
    Q_OBJECT
public:
    explicit ServerController(QObject* parent = nullptr);

    static Server* getServerInstance();
private:
    static Server* m_server;
};

#endif // SERVERCONTROLLER_H
