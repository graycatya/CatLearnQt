#ifndef SERIALPROTOCOLFACTORYBASE_H
#define SERIALPROTOCOLFACTORYBASE_H

#include <QObject>

class SerialProtocolBase;

class SerialProtocolFactoryBase : public QObject
{
    Q_ENUMS(SERIALPROTOCOL)
public:
    enum SERIALPROTOCOL {
    };
    virtual ~SerialProtocolFactoryBase() = 0;
    virtual SerialProtocolBase* CreateProtocol(SERIALPROTOCOL protocol) = 0;

protected:
    SerialProtocolFactoryBase();

};

#endif // SERIALPROTOCOLFACTORYBASE_H
