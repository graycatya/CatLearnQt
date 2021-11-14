#include <QQmlApplicationEngine>
#include <QDebug>
//#include <QQmlContext>
#ifdef QT_WEBENGINE_LIB
#include <QtWebEngine>
#include <QtWebView>
#include <QWebChannel>
#include <QWebSocketServer>
#endif
#ifdef Q_CC_MSVC
#include "CatFrameless/CatFrameLessView.h"
#endif

#include "CatConfig.h"
#ifndef WEBASSEMBLY
#include "SingleApplication"
#include <QmlCatLog.h>
#endif
#include "QmlConfig.h"



int main(int argc, char *argv[])
{
    //QGuiApplication
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#ifdef QT_WEBENGINE_LIB
    QtWebEngine::initialize();
#endif

#ifndef WEBASSEMBLY
    QMLCATLOG::CatLog *catlog = QMLCATLOG::CatLog::Instance();
#endif

#ifndef WEBASSEMBLY
    SingleApplication app(argc, argv);
#else
    QGuiApplication app(argc, argv);
#endif
    app.setOrganizationName("GrayCatYa");
    app.setOrganizationDomain("graycatya.com");
    app.setApplicationName("CatQuickExamples");
#ifndef WEBASSEMBLY
    CatConfig *catconfig = CatConfig::Instance();
    catconfig->InitConfig();


    QmlConfig::moduleRegister();
#endif

#ifdef QT_OS_WIN10
    CatFrameLessView view;

    QObject::connect(&view, &QQuickView::statusChanged,
                     [&view](QQuickView::Status status){
        if(QQuickView::Ready == status)
        {
            view.show();
        }
    });

    view.engine()->addImportPath(GrayCatQtQuickImportPath);
    view.engine()->rootContext()->setContextProperty("view", &view);
#ifndef WEBASSEMBLY
    view.engine()->rootContext()->setContextProperty("catLog", catlog);
#endif
    view.engine()->rootContext()->setContextProperty("catconfig", catconfig);

    QObject::connect(CatConfig::Instance(), SIGNAL(updateLanguage()), view.engine(), SLOT(retranslate()));
    for(QString path : view.engine()->importPathList())
    {
        qDebug() << path;
    }
    view.setMinimumSize({ 900, 600 });
    view.resize(900, 600);
    view.moveToScreenCenter();

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    view.setSource(url);

#else
    QQmlApplicationEngine engine;
    engine.addImportPath(GrayCatQtQuickImportPath);
#ifndef WEBASSEMBLY
    engine.rootContext()->setContextProperty("catLog", catlog);

    engine.rootContext()->setContextProperty("catconfig", catconfig);

    QObject::connect(CatConfig::Instance(), SIGNAL(updateLanguage()), &engine, SLOT(retranslate()));
#endif
    for(QString path : engine.importPathList())
    {
        qDebug() << path;
    }
    engine.load( QUrl( "qrc:/generalmain.qml" ) );
#endif

    return app.exec();
}
