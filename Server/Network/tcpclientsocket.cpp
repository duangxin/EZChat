#include "tcpclientsocket.h"
#include "serverhandlerreg.h"

TcpClientSocket::TcpClientSocket(QObject *parent)
    : QTcpSocket{parent},m_blockSize(0)
{
    connect(this, &QTcpSocket::readyRead, this, &TcpClientSocket::receiveMessage);
    qDebug() << "connect readyRead";
    connect(this, &QTcpSocket::disconnected, this, &TcpClientSocket::onDisconnected);

}

void TcpClientSocket::sendMessage(Msg *message)
{
    if (state() == QAbstractSocket::ConnectedState) {
        write(message->toQByteArray());
                        qDebug() << "服务端发送的数据大小: " << message->toQByteArray().size();
        flush();
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
        qDebug() <<"内部几次";
        QByteArray fullData;
        QDataStream temp(&fullData, QIODevice::WriteOnly);
        temp.setVersion(QDataStream::Qt_6_7);
        temp << static_cast<quint32>(m_blockSize); // 重新加回前面的contentSize
        fullData.append(buf); // 合并为完整格式

        Msg msg = Msg::fromQByteArray(fullData); //客户端收到格式转换后的msg
        qDebug() << "服务端接收到的数据大小: " << fullData.size(); // 打印完整的接收数据大小
        qDebug() << "m_blockSize: " << m_blockSize;
        auto handler = ServerHandlerReg::GetInstance()->getHandler(msg.getType());

        auto socket = qobject_cast<TcpClientSocket *>(sender());    //sender()获取触发这个槽的对象
        if (handler && socket) {
            handler->parse(msg, socket);    //解析处理消息
        }
        m_blockSize = 0;
    }

}

void TcpClientSocket::onDisconnected()
{
    emit clientDisconnected();
}



