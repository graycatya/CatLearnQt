#include "MonitorSerial.h"
#include <QDebug>
#include <QTimer>

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
        QList<QSerialPortInfo> adds;
        QList<QSerialPortInfo> dels;
        adds.clear();
        dels.clear();
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
                    adds.push_back(i.value());
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
                    dels.push_back(i.value());
                }
                i++;
            }
            foreach(auto port , list)
            {
                m_lSerialPortInfo.remove(port);
            }

        } else if(m_lSerialPortInfo.size() == currentports.size())
        {
            QHash<QString, QSerialPortInfo>::const_iterator i = currentports.constBegin();
            while(i != currentports.constEnd()){
                if(!m_lSerialPortInfo.contains(i.key()))
                {
                    adds.push_back(i.value());
                }
                i++;
            }
            i = m_lSerialPortInfo.constBegin();
            while(i != m_lSerialPortInfo.constEnd()){

                if(!currentports.contains(i.key()))
                {
                    dels.push_back(i.value());
                }
                i++;
            }
            m_lSerialPortInfo = currentports;
        }
        if(!adds.isEmpty() || !dels.isEmpty())
        {
            emit UpdateSerial(adds, dels);
        }
        QThread::msleep(FrequencyTime);
    }
}

