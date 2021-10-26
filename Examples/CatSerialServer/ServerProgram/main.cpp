#include <QCoreApplication>
#include "ServerConfig.h"
#include "CatLog"
#include "Src/SerialDevList.h"


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    qRegisterMetaType<QSerialPortInfo>("QSerialPortInfo");
    qRegisterMetaType<QList<QSerialPortInfo>>("QList<QSerialPortInfo>");


    ServerConfig::Instance()->Instance();
    SerialDevList::Instance();
    CATLOG::CatLog::Instance()->__Write_Log(INFO_LOG_T("start SerialServer"));


    return app.exec();
}
