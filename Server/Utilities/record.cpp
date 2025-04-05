#include "record.h"
#include "Utilities/stdDateTime.h"

Record * Record::m_Record = nullptr;
Record::Record(QObject *parent)
    : QObject{parent}
{}

Record *Record::getRecord()
{
    if(!m_Record){
        m_Record = new Record;
    }
    return m_Record;
}

void Record::writeRecord(QString content)
{
    emit readyShowContent(StdDateTime::GetDateTime() + "：" + content);
}
