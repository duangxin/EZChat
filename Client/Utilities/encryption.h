#ifndef ENCRYPTION_H
#define ENCRYPTION_H

//哈希加密
#include <QString>
#include <QCryptographicHash>

class Encryption
{
public:
    Encryption();
    //静态函数才能不实例化就调用
    static QString GetHash(const QString& str);
};

#endif // ENCRYPTION_H
