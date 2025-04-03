#include "encryption.h"

Encryption::Encryption() {}

QString Encryption::GetHash(const QString& str)
{
    QByteArray strData = str.toUtf8(); // 转换为字节数据
    QByteArray hash = QCryptographicHash::hash(strData, QCryptographicHash::Sha256); // 计算哈希
    return hash.toHex(); // 转换为十六进制字符串
}


