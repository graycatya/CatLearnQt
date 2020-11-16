#include "MonitorSerial.h"
#include <QDebug>

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
        m_lSerialPortInfo = QSerialPortInfo::availablePorts();
    } else {
        FirstTimeExamine = false;
    }
    while(m_bStart)
    {
        QList<QSerialPortInfo> temp = QSerialPortInfo::availablePorts();
        if(m_lSerialPortInfo.isEmpty())
        {
            m_lSerialPortInfo = temp;
            foreach(const QSerialPortInfo &portInfo, m_lSerialPortInfo)
            {
                emit AddSerial(portInfo);
            }
        }
        if(m_lSerialPortInfo.size() != temp.size())
        {
            if(m_lSerialPortInfo.size() > temp.size())
            {
                // 端口拨出遍历
                QList<QSerialPortInfo> LastPorts = m_lSerialPortInfo;
                int num = 0;
                foreach(const QSerialPortInfo &removeInfo, LastPorts)
                {
                    foreach(const QSerialPortInfo &portInfo, temp)
                    {
                        if(removeInfo.portName() == portInfo.portName() &&
                                removeInfo.systemLocation() == portInfo.systemLocation())
                        {
                            LastPorts.removeAt(num);
                        }
                    }
                    num++;
                }
                foreach(const QSerialPortInfo &info, LastPorts)
                {
                    emit DeleteSerial(info);
                }
            } else {
                // 端口插入遍历
                QList<QSerialPortInfo> NewPorts = temp;
                int num = 0;
                foreach(const QSerialPortInfo &addInfo, NewPorts)
                {
                    foreach(const QSerialPortInfo &portInfo, m_lSerialPortInfo)
                    {
                        if(addInfo.portName() == portInfo.portName() &&
                                addInfo.systemLocation() == portInfo.systemLocation())
                        {
                            NewPorts.removeAt(num);
                        }
                    }
                    num++;
                }
                foreach(const QSerialPortInfo &info, NewPorts)
                {
                    emit AddSerial(info);
                }
            }
            m_lSerialPortInfo = temp;
        }
        QThread::msleep(FrequencyTime);
    }
}
