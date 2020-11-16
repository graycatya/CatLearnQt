#include "SerialProtocolFactory.h"
#include "SerialProtocolBase.h"

#include "Yet640Protocol.h"

SerialProtocolFactory::SerialProtocolFactory()
{

}

SerialProtocolFactory::~SerialProtocolFactory()
{

}

SerialProtocolBase *SerialProtocolFactory::CreateProtocol(SERIALPROTOCOL protocol)
{
    switch (protocol) {

        case YET640_PROTOCOL: {
            return new Yet640Protocol;
        }

        default: return nullptr;
    }
}
