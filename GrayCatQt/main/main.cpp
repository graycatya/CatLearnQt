//#include <QApplication>
#include <SingleApplication>

int main(int argc, char *argv[])
{
    // [0] 进程单例 - 不可重复打开
    SingleApplication a(argc, argv);
    return a.exec();
}
