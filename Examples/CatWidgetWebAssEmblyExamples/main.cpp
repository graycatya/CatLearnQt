//#include <QApplication>
#include <QApplication>
#include <QTranslator>
#include "WinWidget.h"

#include "CatConfig/CatConfig.h"
#include <QTimer>


int main(int argc, char *argv[])
{
    // 共享窗体上下文，并且防止黑屏出现
    // QApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QApplication app(argc, argv);

    // [2] 配置初始化
    CatConfig::Instance();


    WinWidget w;
    w.show();

    return app.exec();
}

