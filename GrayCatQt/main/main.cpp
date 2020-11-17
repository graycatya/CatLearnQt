//#include <QApplication>
#include <SingleApplication>
#include <CatLog>
#include "MainWindow.h"



int main(int argc, char *argv[])
{
    // [0] 进程单例 - 不可重复打开
    SingleApplication a(argc, argv);
    CATLOG::CatLog::Instance();


    MainWindow window;
    window.show();

    QString log1 = "main size: "
            + QString::number(window.width())
            + " : "
            + QString::number(window.height())
            + " x: "
            + QString::number(window.x())
            + " y: "
            + QString::number(window.y());

    CATLOG::CatLog::__Write_Log(DEBUG_LOG_T(log1.toStdString()));

    return a.exec();
}
