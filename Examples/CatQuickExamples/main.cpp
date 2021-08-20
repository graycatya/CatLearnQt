#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QQmlContext>
#ifdef QT_WEBENGINE_LIB
#include <QtWebEngine>
#include <QtWebView>
#include <QWebChannel>
#include <QWebSocketServer>
#include "Src/WebChannelFunction/CatEchatswebChannel.h"
#endif
#ifdef Q_CC_MSVC
#include "CatFrameless/CatFrameLessView.h"
#endif
#include "QrenCode/QuickQrenCodeParentItem.h"
#include <QmlCatLog.h>
#include "CatConfig.h"


int main(int argc, char *argv[])
{
    //QGuiApplication
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#ifdef QT_WEBENGINE_LIB
    QtWebEngine::initialize();
#endif
    QMLCATLOG::CatLog *catlog = QMLCATLOG::CatLog::Instance();

    QGuiApplication app(argc, argv);
    app.setOrganizationName("Some Company");
    app.setOrganizationDomain("somecompany.com");
    app.setApplicationName("CatQuickExamples");

    //qDebug() <<  app.sessionId();

    CatConfig *catconfig = CatConfig::Instance();
    catconfig->InitConfig();

    qmlRegisterType<QuickQrenCodeParentItem>("QParentQrenCode", 1, 0, "ParentQrenCode");
#ifdef QT_WEBENGINE_LIB
    qmlRegisterType<CatEchatswebChannel>("io.decovar.CatEchatswebChannel", 1, 0, "CatEchatswebChannel");
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

    //view.engine()->addImportPath(TaoQuickImportPath);
    view.engine()->addImportPath(GrayCatQtQuickImportPath);
    view.engine()->rootContext()->setContextProperty("view", &view);
    view.engine()->rootContext()->setContextProperty("catLog", catlog);
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
    engine.rootContext()->setContextProperty("catLog", catlog);
    engine.rootContext()->setContextProperty("catconfig", catconfig);

    QObject::connect(CatConfig::Instance(), SIGNAL(updateLanguage()), &engine, SLOT(retranslate()));
    for(QString path : engine.importPathList())
    {
        qDebug() << path;
    }
    engine.load( QUrl( "qrc:/generalmain.qml" ) );
#endif

    return app.exec();
}
