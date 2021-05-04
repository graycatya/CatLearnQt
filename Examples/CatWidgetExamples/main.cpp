//#include <QApplication>
#include <SingleApplication>
#include <CatLog>
#include <QTranslator>
#include "WinWidget.h"

#include "CatConfig/CatConfig.h"
#include <QTimer>
/*
#ifndef Q_OS_IOS
#include <CatSerial>
#endif*/


int main(int argc, char *argv[])
{
    // 共享窗体上下文，并且防止黑屏出现
    QApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    // [0] 进程单例 - 不可重复打开
    SingleApplication app(argc, argv);

    // [1] 启动日志模块
    CATLOG::CatLog::Instance();
    CATLOG::CatLog::__Write_Log(INFO_LOG_T("Init System!"));

    // [2] 配置初始化
    CatConfig *config = CatConfig::Instance();
    config->SetTranslator(&app);
    config->InitConfig();
#ifndef Q_OS_IOS
    // [3] 启动串口热插拔检测
/*  MonitorSerial::Instance()->Start(200, true);
    QObject::connect(MonitorSerial::Instance(), &MonitorSerial::UpdateSerial, [](QList<QSerialPortInfo> adds, QList<QSerialPortInfo> dels){
        for(auto info : adds)
        {
            QString log = "AddSerial: " + info.portName() + " " + QString::number(info.productIdentifier()) + " : " + QString::number(info.vendorIdentifier());
            CATLOG::CatLog::__Write_Log(INFO_LOG_T(log.toStdString()));
        }
        for(auto info : dels)
        {
            QString log = "DeleteSerial: " + info.portName() + " " + QString::number(info.productIdentifier()) + " : " + QString::number(info.vendorIdentifier());
            CATLOG::CatLog::__Write_Log(INFO_LOG_T(log.toStdString()));
        }
    });*/
#endif

    WinWidget w;
    w.show();

    return app.exec();
}

