//#include <QApplication>
#ifndef WEBASSEMBLY
    #include <QApplication>
#else
    #include <QApplication>
#endif
#include <QTranslator>
#include "WinWidget.h"


#include "CatConfig/CatConfig.h"
#include <QTimer>

#include <QLibraryInfo>
#include <QQuickWindow>

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

    QApplication app(argc, argv);


#if (QT_VERSION > QT_VERSION_CHECK(6,0,0))
    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);
#endif
    QCoreApplication::addLibraryPath("../");

    qDebug() << "Init System!";

    qDebug() <<  QLibraryInfo::location(QLibraryInfo::PrefixPath);
    qDebug() <<  QLibraryInfo::location(QLibraryInfo::LibrariesPath);
    qDebug() <<  QLibraryInfo::location(QLibraryInfo::LibraryExecutablesPath);
    qDebug() <<  QLibraryInfo::location(QLibraryInfo::BinariesPath);
#if (QT_VERSION < QT_VERSION_CHECK(6,0,0))
    qDebug() <<  QLibraryInfo::location(QLibraryInfo::ImportsPath);
#endif
    qDebug() <<  QLibraryInfo::location(QLibraryInfo::Qml2ImportsPath);
    qDebug() <<  QLibraryInfo::location(QLibraryInfo::TranslationsPath);


    // [2] 配置初始化
    CatConfig *config = CatConfig::Instance();
    config->SetTranslator(&app);
    config->InitConfig();

    WinWidget w;
    w.show();

    return app.exec();
}

