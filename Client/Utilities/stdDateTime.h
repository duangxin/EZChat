#ifndef STDDATETIME_H
#define STDDATETIME_H

#include <QDateTime>
class StdDateTime:public QDateTime
{
public:
    explicit StdDateTime(QDateTime *parent = nullptr);
    static QString GetDateTime(){
        return (QDateTime::currentDateTime()).toString("yyyy-MM-dd hh:mm:ss");
    }
    static QString GetDateTimeFileFormat(){
        return (QDateTime::currentDateTime()).toString("yyyy_MM_dd_hh_mm_ss_ms");
    }
};
#endif // STDDATETIME_H
