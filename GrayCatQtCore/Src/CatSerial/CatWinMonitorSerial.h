#ifndef CATWINMONITORSERIAL_H
#define CATWINMONITORSERIAL_H

#include <QObject>

#include <QMutex>

#include <QMap>

class CatWinMonitorSerial : public QObject
{
    Q_OBJECT
public:
    static CatWinMonitorSerial* Instance() noexcept
    {
        if(_instance == nullptr)
        {
            m_pMutex->lock();
            if(_instance == nullptr)
            {
                _instance = new CatWinMonitorSerial;
            }
            m_pMutex->unlock();
        }
        return _instance;
    }

    static void Delete( void ) noexcept
    {
        if(_instance != nullptr)
        {
            if(m_pMutex != nullptr)
            {
                delete m_pMutex;
                m_pMutex = nullptr;
            }
            delete _instance;
            _instance = nullptr;
        }
    }

    static QStringList Serials();

    QMap<QString, QString> m_pSerials;

private:
    CatWinMonitorSerial();
    ~CatWinMonitorSerial();

signals:
    // 端口插入
    void AddSerial(qint64 pid, qint64 vid, QString serial);
    // 端口拔出
    void DeleteSerial(qint64 pid, qint64 vid, QString serial);
    // 端口插入
    //void AddSerial(QSerialPortInfo);
    // 端口拔出


private:
    static CatWinMonitorSerial* _instance;

    static QMutex* m_pMutex;

};

#endif // CATWINMONITORSERIAL_H
