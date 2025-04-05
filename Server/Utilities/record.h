#ifndef RECORD_H
#define RECORD_H

#include <QObject>
//记录服务器端日志


class Record : public QObject
{
    Q_OBJECT
public:
    explicit Record(QObject *parent = nullptr);

    static Record * getRecord();
    void writeRecord(QString content);

signals:
    void readyShowContent(QString content);

private:
    static Record * m_Record;
};
#endif // RECORD_H
