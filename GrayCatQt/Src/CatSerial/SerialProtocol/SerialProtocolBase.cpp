#include "SerialProtocolBase.h"
#include <QUuid>

SerialProtocolBase::~SerialProtocolBase() {

}

uint16_t SerialProtocolBase::ec_crc_calc(uint8_t *ptr, uint32_t len)
{
    uint8_t crc_H4 = 0;
    uint16_t crc = 0;
    const uint16_t crc_table[16] = {
    0x0000,0x1021,0x2042,0x3063,0x4084,0x50a5,0x60c6,0x70e7,
    0x8108,0x9129,0xa14a,0xb16b,0xc18c,0xd1ad,0xe1ce,0xf1ef };
    while (len--)
    {
        crc_H4 = (uint8_t)(crc >> 12);
        crc = crc << 4;
        crc = crc ^ crc_table[crc_H4 ^ (*ptr >> 4)];
        crc_H4 = (uint8_t)(crc >> 12);
        crc = crc << 4;
        crc = crc ^ crc_table[crc_H4 ^ (*ptr & 0x0f)];
        ptr++;
    }
    return(crc);
}

QString SerialProtocolBase::GenerateGuid()
{
    return QUuid::createUuid().toString();
}

float SerialProtocolBase::ArrayConvertFloat(const uchar array[])
{
    float f = *((float*)array);
    return f;
}

QByteArray SerialProtocolBase::FloatConvertArray(float data)
{
    QByteArray array;
    uchar temp[4];
    memcpy(temp,&data,4);
    array.clear();
    array.push_back(temp[0]);
    array.push_back(temp[1]);
    array.push_back(temp[2]);
    array.push_back(temp[3]);
    return array;
}

void SerialProtocolBase::ReadSerialData(QByteArray &data)
{
    this->DecodeData(data);
}

SerialProtocolBase::SerialProtocolBase(QObject *parent)
    : QObject(parent)
    , m_yState(NONE)
{

}
