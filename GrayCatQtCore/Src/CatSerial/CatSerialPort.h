#ifndef CATSERIALPORT_H
#define CATSERIALPORT_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <CatLog>

class ReadDataBufferWork : public QThread
{
    Q_OBJECT
public:
    explicit ReadDataBufferWork(QObject *parent = nullptr)
        : QThread(parent)
        , m_bWork(false)
        , m_ySleep(0)
    {

    }

    ~ReadDataBufferWork()
    {
        m_bWork = false;
        this->wait();
    }

    void Start(int sleep)
    {

            //m_bWork = true;
        m_ySleep = sleep;
        this->start();

    }

    bool GetWork( void )
    {
        return m_bWork;
    }

    void SetSerialPort(QSerialPort *port)
    {
        this->port = port;
    }

signals:
    void readyRead();

protected:
    void run() override
    {

        m_bWork = true;
        this->msleep(m_ySleep);
        emit readyRead();
        m_bWork = false;

    }

private:
    QSerialPort *port = nullptr;
    bool m_bWork;
    int m_ySleep;

};


class ReadPortDataWork : public QThread
{
    Q_OBJECT
public:
    explicit ReadPortDataWork(QObject *parent = nullptr)
        : QThread(parent)
        , m_bWork(false)
        , m_ySleep(0)
    {

    }

    ~ReadPortDataWork()
    {
        this->wait();
    }

    void Start(int sleep)
    {
        m_ySleep = sleep;
        this->start();
    }

    bool GetWork( void )
    {
        return m_bWork;
    }

    void SetSerialPort(QSerialPort *port)
    {
        this->port = port;
    }

signals:
    void UpdateReadWork();

protected:
    void run() override
    {
        m_bWork = true;
        this->msleep(m_ySleep);
        m_bWork = false;
        emit UpdateReadWork();
    }

private:
    QSerialPort *port = nullptr;
    bool m_bWork;
    int m_ySleep;

};

class CatSerialPort : public QObject
{
    Q_OBJECT
public:
    explicit CatSerialPort(QObject *parent = nullptr);
    ~CatSerialPort();

    void SetSerialInfo(const QSerialPortInfo info);
    void SetSerialPortName(const QString portname);

    QString GetPortName( void );

    bool OpenSerial(qint32 baudRate = QSerialPort::Baud9600, QSerialPort::StopBits stopBits = QSerialPort::OneStop);

    bool IsOpen();

    void Close();

    QSerialPortInfo GetSerialProtInfo(QString port);

    QSerialPort* GetSerialPort();

    void Clear();

signals:
    void ReadSerialPort(QByteArray);
    void ErrorSerialPort(QString);
    void OpenSuccess();
    void DisconnectPort();
    void Closeed();

private:
    void InitProperty();
    void InitConnect();

public slots:
    void WriteSerialPortSlot(QByteArray, bool waitread = false, int msecs = 1000);

private:
    QSerialPortInfo m_qPortInfo;
    QString m_sSerialPortName;
    QByteArray m_yWriteData;
    QByteArray m_yReadData;
    QSerialPort m_qPort;

    ReadPortDataWork *m_pReadPortDataWork;
    ReadDataBufferWork *m_pReadDataBufferWork;

};

#endif // CATSERIALPORT_H

