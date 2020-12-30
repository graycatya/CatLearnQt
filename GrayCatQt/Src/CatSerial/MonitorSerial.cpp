#include "MonitorSerial.h"

MonitorSerial* MonitorSerial::_instance = nullptr;
QMutex* MonitorSerial::m_pMutex = new QMutex;
bool MonitorSerial::m_bStart = false;
bool MonitorSerial::TheFirstTimeExamine = false;
int MonitorSerial::FrequencyTime = 500;

void MonitorSerial::run()
{
    static bool FirstTimeExamine = TheFirstTimeExamine;

    if(!FirstTimeExamine)
    {
        for(auto temp : QSerialPortInfo::availablePorts())
        {
            m_lSerialPortInfo[temp.portName()] = temp;
        }
    } else {
        FirstTimeExamine = false;
    }
    while(m_bStart)
    {
        QHash<QString, QSerialPortInfo> currentports;
        for(auto temp : QSerialPortInfo::availablePorts())
        {
            currentports[temp.portName()] = temp;
        }
        if(m_lSerialPortInfo.size() < currentports.size())
        {
            QHash<QString, QSerialPortInfo>::const_iterator i = currentports.constBegin();
            while(i != currentports.constEnd())
            {
                if(!m_lSerialPortInfo.contains(i.key()))
                {
                    m_lSerialPortInfo[i.key()] = i.value();
                    emit AddSerial(i.value());
                }
                i++;
            }
        } else if(m_lSerialPortInfo.size() > currentports.size()) {
            QHash<QString, QSerialPortInfo>::const_iterator i = m_lSerialPortInfo.constBegin();
            QStringList list;
            list.clear();
            while(i != m_lSerialPortInfo.constEnd())
            {
                if(!currentports.contains(i.key()))
                {
                    list << i.key();
                    emit DeleteSerial(i.value());
                }
                i++;
            }
            foreach(auto port , list)
            {
                m_lSerialPortInfo.remove(port);
            }

        }else if(m_lSerialPortInfo.size() == currentports.size())
        {
            QHash<QString, QSerialPortInfo>::const_iterator i = currentports.constBegin();
            QList<QSerialPortInfo> adds;
            QList<QSerialPortInfo> dels;
            while(i != currentports.constEnd()){
                if(!m_lSerialPortInfo.contains(i.key()))
                {
                    adds.push_back(i.value());
                    QString log = "add " + i.key();
                    CATLOG::CatLog::__Write_Log(DEBUG_LOG_T(log.toStdString()));
                }
                i++;
            }
            i = m_lSerialPortInfo.constBegin();
            while(i != m_lSerialPortInfo.constEnd()){

                if(!currentports.contains(i.key()))
                {
                    dels.push_back(i.value());
                    QString log = "del " + i.key();
                    CATLOG::CatLog::__Write_Log(DEBUG_LOG_T(log.toStdString()));
                }
                i++;
            }
            emit UpdateSerial(adds, dels);
            //qDebug() << m_lSerialPortInfo.keys() << " | " << currentports.keys();
            m_lSerialPortInfo = currentports;
        }
        QThread::msleep(FrequencyTime);
    }
}
