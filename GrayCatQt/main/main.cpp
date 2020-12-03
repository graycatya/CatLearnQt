//#include <QApplication>
#include <SingleApplication>
#include <CatLog>
#include <CatSerial>
#include "WinWidget.h"

#include <QSettings>


int main(int argc, char *argv[])
{
    // [0] 进程单例 - 不可重复打开
    SingleApplication a(argc, argv);
    // 启动日志模块
    CATLOG::CatLog::Instance();
    CATLOG::CatLog::__Write_Log(INFO_LOG_T("Init System!"));
    // 启动串口热插拔检测
    MonitorSerial::Instance()->Start(200, true);
    QObject::connect(MonitorSerial::Instance(), &MonitorSerial::AddSerial, [](QSerialPortInfo info){
        QString log = "AddSerial: " + info.portName() + " " + QString::number(info.productIdentifier()) + " : " + QString::number(info.vendorIdentifier());
        CATLOG::CatLog::__Write_Log(INFO_LOG_T(log.toStdString()));
    });
    QObject::connect(MonitorSerial::Instance(), &MonitorSerial::DeleteSerial, [](QSerialPortInfo info){
        QString log = "DeleteSerial: " + info.portName() + " " + QString::number(info.productIdentifier()) + " : " + QString::number(info.vendorIdentifier());
        CATLOG::CatLog::__Write_Log(INFO_LOG_T(log.toStdString()));
    });

    QSettings settings("GrayCatYa", APP_NAME);

    WinWidget w;
    w.setMinimumSize(QSize(300, 300));
    w.show();

    return a.exec();
}
