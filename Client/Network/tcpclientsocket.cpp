#include "tcpclientsocket.h"
#include "clienthandlerreg.h"

TcpClientSocket::TcpClientSocket(QObject *parent) :
    QTcpSocket(parent)
{
    //服务器连接状态
    connect(this, &QTcpSocket::stateChanged, [](QAbstractSocket::SocketState state) {
        qDebug() << "Socket state changed:" << state;
    });

    //sendMessage是否成功
    connect(this, &QTcpSocket::bytesWritten, this, [](qint64 bytes) {
        qDebug() << bytes << " bytes written successfully.";
    });
    connect(this, &QTcpSocket::readyRead, this, &TcpClientSocket::receiveMessage);
}

void TcpClientSocket::setServerIP(const QString &serverIP)
{
    m_serverIP = serverIP;
}

void TcpClientSocket::setServerTcpPort(const quint16 &serverTcpPort)
{
    m_serverTcpPort = serverTcpPort;
}

QString TcpClientSocket::getServerIP()
{
    return m_serverIP;
}

quint16 TcpClientSocket::getServerPort()
{
    return m_serverTcpPort;
}

void TcpClientSocket::connectToServer()
{
    abort();  // 终止当前连接，准备新连接

    connectToHost(QHostAddress(this->m_serverIP), this->m_serverTcpPort);


}

void TcpClientSocket::sendMessage(Msg* message)
{

    if (state() == QAbstractSocket::ConnectedState) {
        write(message->toQByteArray());
                qDebug() << "客户端发送的数据大小: " << message->toQByteArray().size();
        flush();//尽快发送
        //这样会阻塞UI，改用信号与槽
        //waitForBytesWritten();  //阻塞等待数据写入到底层设备,防止在缓冲区还没发出去
    }

}

void TcpClientSocket::receiveMessage()
{
    //接收消息|4:contentSize|2:type|?:content|
    QDataStream in(this);
    in.setVersion(QDataStream::Qt_6_7);

    while (true) {
        //先一口气读四字节，确定msg长度
        if (m_blockSize == 0) {
            if (bytesAvailable() < static_cast<int>(sizeof(quint32)))
                return;
            in >> m_blockSize;
        }
        //再等待，直到数据全部到达
        if (bytesAvailable() < static_cast<int>(m_blockSize + sizeof(quint16)))  // 再等 type + content
            return;
        //要包括type和content
        QByteArray buf = in.device()->read(m_blockSize + sizeof(quint16));
        if (buf.size() < m_blockSize + sizeof(quint16)) {
            qWarning() << "读取数据不足，可能被截断，返回";
            return;
        }

        QByteArray fullData;
        QDataStream temp(&fullData, QIODevice::WriteOnly);
        temp.setVersion(QDataStream::Qt_6_7);
        temp << static_cast<quint32>(m_blockSize); // 重新加回前面的contentSize
        fullData.append(buf); // 合并为完整格式

        Msg msg = Msg::fromQByteArray(fullData); //客户端收到格式转换后的msg

        qDebug() << "客户端接收到的数据大小: " << fullData.size(); // 打印完整的接收数据大小
        // qDebug() << "m_blockSize: " << m_blockSize;
        // qDebug() << "msg type = " << static_cast<int>(msg.getType());
        auto handler = ClientHandlerReg::GetInstance()->getHandler(msg.getType());
        if (handler) {
            handler->parse(msg);
        } else {
            qWarning() << "找不到消息类型的 handler";
        }//解析处理消息
        m_blockSize = 0;
    }

}
