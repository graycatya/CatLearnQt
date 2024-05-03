#ifndef SERIALDEVLIST_H
#define SERIALDEVLIST_H

#include <QObject>
#include <QMutex>
#include "CatSerial"

class SerialState;

class SerialDevList : public QObject
{
    Q_OBJECT
public:
    static SerialDevList* Instance() noexcept
    {
        if(_instance == nullptr)
        {
            m_pMutex->lock();
            if(_instance == nullptr)
            {
                _instance = new SerialDevList;
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

    QList<QString> GetSerialDevList();

    void OpenSerialPort(QString port, qint32 baudRate, int stopBits);
    void CloseSerialPort(QString port);
    void WriteData(QString port, QByteArray data);


signals:
    void SerialOpenSucceed(QString port);
    void SerialCloseSucceed(QString port);
    void SerialDisconnect(QString port);
    void SerialError(QString port, quint64 error);
    void ReadData(QString port, QByteArray data);
    //void SerialLists(QList<QString> ports);
    void AddDev(QString port);
    void DelDev(QString port);


private:
    SerialDevList();
    ~SerialDevList();

    void InitConnect();

    void AddDevs(QList<QSerialPortInfo> devs);
    void DelDevs(QList<QSerialPortInfo> devs);

    bool IsDev(QSerialPortInfo &info);

private:
    static SerialDevList* _instance;
    static QMutex* m_pMutex;
    QHash<QString, SerialState*> m_ySerials;

};

#endif // SERIALDEVLIST_H
