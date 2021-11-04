#include <QCoreApplication>
#include "ServerConfig.h"
#include "CatLog"
#include "Src/SerialDevList.h"
#include "Src/SerialServerInitialize.h"


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setApplicationName("CatSerialServer");

    qRegisterMetaType<QSerialPortInfo>("QSerialPortInfo");
    qRegisterMetaType<QList<QSerialPortInfo>>("QList<QSerialPortInfo>");


    ServerConfig::Instance()->Instance();
    SerialDevList::Instance();
    CATLOG::CatLog::Instance()->__Write_Log(INFO_LOG_T("start SerialServer"));

    SerialServerInitialize initialize;

    return app.exec();
}
