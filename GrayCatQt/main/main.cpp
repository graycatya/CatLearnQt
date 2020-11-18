//#include <QApplication>
#include <SingleApplication>
#include <CatLog>
#include <CatSerial>
#include "WinWidget.h"



int main(int argc, char *argv[])
{
    // [0] 进程单例 - 不可重复打开
    SingleApplication a(argc, argv);
    // 启动日志模块
    CATLOG::CatLog::Instance();
    // 启动串口热插拔检测
    MonitorSerial::Instance()->Start(200, 300);


    WinWidget w;
    w.setMinimumSize(QSize(300, 300));
    w.show();

    return a.exec();
}
