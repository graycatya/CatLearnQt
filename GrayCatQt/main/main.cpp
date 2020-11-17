//#include <QApplication>
#include <SingleApplication>
#include <CatLog>




int main(int argc, char *argv[])
{
    // [0] 进程单例 - 不可重复打开
    SingleApplication a(argc, argv);
    CATLOG::CatLog::Instance();
    std::thread th([](){

        CATLOG::CatLog::__Write_Log(DEBUG_LOG_T("test"));
    });
    th.join();


    std::thread ths([](){

        CATLOG::CatLog::__Write_Log(DEBUG_LOG_T("test"));
    });
    ths.join();
    CATLOG::CatLog::__Write_Log(DEBUG_LOG_T("test"));


    return a.exec();
}
