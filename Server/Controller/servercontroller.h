#ifndef SERVERCONTROLLER_H
#define SERVERCONTROLLER_H
#include "Network/server.h"

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
