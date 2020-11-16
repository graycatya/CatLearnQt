#include "SerialDevFilter.h"

QVector<QString> SerialDevFilter::m_vPidVid = {
    "00000,0000"
};


bool SerialDevFilter::IsDev(QSerialPortInfo &info)
{
    for (int i = 0; i < m_vPidVid.size(); ++i) {
        if (m_vPidVid.at(i) == QString(QString::number(info.productIdentifier())
                                       + "," +
                                       QString::number(info.vendorIdentifier())))
        {
            return true;
        }
    }
    return false;
}

