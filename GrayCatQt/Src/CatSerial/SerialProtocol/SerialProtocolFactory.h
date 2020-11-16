#ifndef SERIALPROTOCOLFACTORY_H
#define SERIALPROTOCOLFACTORY_H

#include "SerialProtocolFactoryBase.h"

class SerialProtocolBase;

class SerialProtocolFactory : public SerialProtocolFactoryBase
{
public:
    SerialProtocolFactory();
    ~SerialProtocolFactory();

    SerialProtocolBase* CreateProtocol(SERIALPROTOCOL protocol = YET640_PROTOCOL);
};

#endif // SERIALPROTOCOLFACTORY_H
