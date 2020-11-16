#ifndef SERIALPROTOCOLFACTORYBASE_H
#define SERIALPROTOCOLFACTORYBASE_H

#include <QObject>

class SerialProtocolBase;

class SerialProtocolFactoryBase : public QObject
{
    Q_ENUMS(SERIALPROTOCOL)
public:
    enum SERIALPROTOCOL {
        YET640_PROTOCOL
    };
    virtual ~SerialProtocolFactoryBase() = 0;
    virtual SerialProtocolBase* CreateProtocol(SERIALPROTOCOL protocol = YET640_PROTOCOL) = 0;

protected:
    SerialProtocolFactoryBase();

};

#endif // SERIALPROTOCOLFACTORYBASE_H
