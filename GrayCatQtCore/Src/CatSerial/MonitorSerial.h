#ifndef MONITORSERIAL_H
#define MONITORSERIAL_H

/**
* @brief         用于串口设备热插拔监测，以及串口设备信息
* @author        Cat
* @date          2020-10-26
*/

#include <QThread>
#include <QMutex>
#include <QSerialPortInfo>
#include <QHash>

class MonitorSerial : public QThread
{
    Q_OBJECT
public:
    static MonitorSerial* Instance() noexcept
    {
        if(_instance == nullptr)
        {
            m_pMutex->lock();
            if(_instance == nullptr)
            {
                _instance = new MonitorSerial;
            }
            m_pMutex->unlock();
        }
        return _instance;
    }

    static void Delete( void ) noexcept
    {
        if(_instance != nullptr)
        {
            if(_instance->IsStart())
            {
                m_pMutex->lock();
                m_bStart = false;
                m_pMutex->unlock();
                _instance->wait();
                if(m_pMutex != nullptr)
                {
                    delete m_pMutex;
                    m_pMutex = nullptr;
                }
            }
            delete _instance;
            _instance = nullptr;
        }
    }

    void Start(int frequencytime = 200, bool thefirsttimeexamine = false) noexcept
    {
        if(!_instance->IsStart())
        {
            FrequencyTime = frequencytime;
            m_bStart = true;
            TheFirstTimeExamine = thefirsttimeexamine;
            _instance->start();
        }
    }

    static bool IsStart( void ) noexcept
    {
        return m_bStart;
    }

    QHash<QString, QSerialPortInfo> GetSerialPortInfo() noexcept
    {
        return m_lSerialPortInfo;
    }

protected:
    void run() override;

signals:
    // 端口插入
    //void AddSerial(QSerialPortInfo);
    // 端口拔出
    //void DeleteSerial(QSerialPortInfo);
    // 同时获取插入与拔出的端口
    void UpdateSerial(QList<QSerialPortInfo> adds, QList<QSerialPortInfo> dels);

private:
    MonitorSerial() {
        m_lSerialPortInfo.clear();
    }
    ~MonitorSerial() {}

    static MonitorSerial* _instance;
    static QMutex* m_pMutex;
    static bool m_bStart;
    static int FrequencyTime;
    static bool TheFirstTimeExamine;
    QHash<QString, QSerialPortInfo> m_lSerialPortInfo;


};

#endif // MONITORSERIAL_H
