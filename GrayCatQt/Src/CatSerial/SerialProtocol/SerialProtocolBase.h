#ifndef SERIALPROTOCOLBASE_H
#define SERIALPROTOCOLBASE_H

#include <QByteArray>
#include <QObject>

class SerialProtocolBase : public QObject
{
    Q_OBJECT
    Q_ENUMS(SERIALSTATE)
public:
    enum SERIALSTATE {
        NONE,           // 无状态
        //WRITE,          // 写状态
        //READ,           // 读状态
        ENCODE,         // 编码-组包
        DECODE,         // 解码-解包
        PROTOCOLERROR   // 协议错误
    };

    virtual ~SerialProtocolBase() = 0;
    virtual QByteArray EncodeData(QByteArray&) = 0;
    virtual QByteArray DecodeData(QByteArray&) = 0;

public:
    uint16_t ec_crc_calc(uint8_t *ptr, uint32_t len);
    //生成随机数Guid
    QString GenerateGuid();
    // 4字节转float
    float ArrayConvertFloat(const uchar array[4]);
    QByteArray FloatConvertArray(float data);

signals:
    void Stateed(SERIALSTATE);
    void WriteSerialDataed(QByteArray);

public slots:
    // 读串口数据槽函数
    void ReadSerialData(QByteArray&);

protected:
    explicit SerialProtocolBase(QObject *parent = nullptr);

private:
    SERIALSTATE m_yState;

};

#endif // SERIALPROTOCOLBASE_H
