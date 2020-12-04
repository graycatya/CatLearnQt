//#include <QApplication>
#include <SingleApplication>
#include <CatLog>
#include <CatSerial>
#include "WinWidget.h"

#include "CatConfig/CatConfig.h"
#include <QTimer>


int main(int argc, char *argv[])
{
    // [0] 进程单例 - 不可重复打开
    SingleApplication a(argc, argv);

    // [1] 配置初始化
    CatConfig::Instance();

    // [2] 启动日志模块
    CATLOG::CatLog::Instance();
    CATLOG::CatLog::__Write_Log(INFO_LOG_T("Init System!"));

    // [3] 启动串口热插拔检测
    MonitorSerial::Instance()->Start(200, true);
    QObject::connect(MonitorSerial::Instance(), &MonitorSerial::AddSerial, [](QSerialPortInfo info){
        QString log = "AddSerial: " + info.portName() + " " + QString::number(info.productIdentifier()) + " : " + QString::number(info.vendorIdentifier());
        CATLOG::CatLog::__Write_Log(INFO_LOG_T(log.toStdString()));
    });

    QObject::connect(MonitorSerial::Instance(), &MonitorSerial::DeleteSerial, [](QSerialPortInfo info){
        QString log = "DeleteSerial: " + info.portName() + " " + QString::number(info.productIdentifier()) + " : " + QString::number(info.vendorIdentifier());
        CATLOG::CatLog::__Write_Log(INFO_LOG_T(log.toStdString()));
    });

    WinWidget w;
    w.show();

    return a.exec();
}