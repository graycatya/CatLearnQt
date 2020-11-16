#ifndef SERIALDEVFILTER_H
#define SERIALDEVFILTER_H

#include <QThread>
#include <QSerialPortInfo>
#include <QMutex>
#include <QWaitCondition>


class SerialDevFilter : public QObject
{
    Q_OBJECT
public:
    SerialDevFilter() {
        //m_vPidVid.clear();
    }

    ~SerialDevFilter() {}

    static bool IsDev(QSerialPortInfo &info);

private:


private:
    static QVector<QString> m_vPidVid;

};

#endif // SERIALDEVFILTER_H
