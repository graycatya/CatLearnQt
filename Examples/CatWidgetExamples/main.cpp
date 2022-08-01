//#include <QApplication>
#ifndef WEBASSEMBLY
    #include <SingleApplication>
    #include <QApplication>
#else
    #include <QApplication>
#endif
#include <CatLog>
#include <QTranslator>
#include "WinWidget.h"
#include "WinMainWidget.h"

#include "CatConfig/CatConfig.h"
#include <QTimer>

#include <QLibraryInfo>

#ifndef Q_OS_IOS
#include "utilities.h"
#endif


int main(int argc, char *argv[])
{
    // 共享窗体上下文，并且防止黑屏出现
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QCoreApplication::setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::Round);
#endif
    // [0] 进程单例 - 不可重复打开
#ifndef WEBASSEMBLY
    SingleApplication app(argc, argv);
#else
    QApplication app(argc, argv);
#endif


    QCoreApplication::addLibraryPath("../");
    // [1] 启动日志模块
    CATLOG::CatLog::Instance();
    CATLOG::CatLog::__Write_Log(INFO_LOG_T("Init System!"));

    CATLOG::CatLog::__Write_Log("./log", INFO_LOG_T(QLibraryInfo::location(QLibraryInfo::PrefixPath).toStdString()));
    CATLOG::CatLog::__Write_Log("./log", INFO_LOG_T(QLibraryInfo::location(QLibraryInfo::LibrariesPath).toStdString()));
    CATLOG::CatLog::__Write_Log("./log", INFO_LOG_T(QLibraryInfo::location(QLibraryInfo::LibraryExecutablesPath).toStdString()));
    CATLOG::CatLog::__Write_Log("./log", INFO_LOG_T(QLibraryInfo::location(QLibraryInfo::BinariesPath).toStdString()));
#if (QT_VERSION < QT_VERSION_CHECK(6,0,0))
    CATLOG::CatLog::__Write_Log("./log", INFO_LOG_T(QLibraryInfo::location(QLibraryInfo::ImportsPath).toStdString()));
#endif
    CATLOG::CatLog::__Write_Log("./log", INFO_LOG_T(QLibraryInfo::location(QLibraryInfo::Qml2ImportsPath).toStdString()));
    CATLOG::CatLog::__Write_Log("./log", INFO_LOG_T(QLibraryInfo::location(QLibraryInfo::TranslationsPath).toStdString()));


    // [2] 配置初始化
    CatConfig *config = CatConfig::Instance();
    config->SetTranslator(&app);
    config->InitConfig();

    WinMainWidget w;
    w.show();

    return app.exec();
}

