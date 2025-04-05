#include "servercontroller.h"


Server* ServerController::m_server = nullptr;

ServerController::ServerController(QObject *parent)
{

}

Server* ServerController::getServerInstance()
{
    if (!m_server) {
        m_server = new Server();
    }
    return m_server;
}
