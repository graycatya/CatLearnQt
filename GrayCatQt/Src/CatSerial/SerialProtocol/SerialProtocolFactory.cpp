#include "SerialProtocolFactory.h"
#include "SerialProtocolBase.h"

SerialProtocolFactory::SerialProtocolFactory()
{

}

SerialProtocolFactory::~SerialProtocolFactory()
{

}

SerialProtocolBase *SerialProtocolFactory::CreateProtocol(SERIALPROTOCOL protocol)
{
    switch (protocol) {
        default: return nullptr;
    }
}
