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
    window.move(300, 200);


    return a.exec();
}
