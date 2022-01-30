#include <QQmlApplicationEngine>
#include <QDebug>
#include <QVariant>
//#include <QQmlContext>
#ifdef QT_WEBENGINE_LIB
#include <QtWebEngine>
#include <QtWebView>
#include <QWebChannel>
#include <QWebSocketServer>
#endif
#ifdef Q_CC_MSVC
#include "CatFrameLessView.h"
#endif

#include "CatConfig.h"
#ifndef WEBASSEMBLY
#include "SingleApplication"
#include "QmlCatLog.h"
#endif
#include "QmlConfig.h"
#include <QtQuickControls2/qquickstyle.h>

int main(int argc, char *argv[])
{
    //QGuiApplication
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#ifdef QT_WEBENGINE_LIB
    QtWebEngine::initialize();
#endif

    QCoreApplication::setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::Round);
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

#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
    QQuickStyle::setStyle(QStringLiteral("Basic"));
#else
    QQuickStyle::setStyle(QStringLiteral("Default"));
#endif
#ifndef WEBASSEMBLY
    CatConfig *catconfig = CatConfig::Instance();
    catconfig->InitConfig();


    QmlConfig::moduleRegister();
#endif


    QQmlApplicationEngine engine;


    engine.addImportPath(GrayCatQtQuickImportPath);
    //engine.rootContext()->setContextProperty("view", &view);
#ifndef WEBASSEMBLY
    engine.rootContext()->setContextProperty("catLog", catlog);
#endif
    engine.rootContext()->setContextProperty("catconfig", catconfig);

    QObject::connect(CatConfig::Instance(), SIGNAL(updateLanguage()), &engine, SLOT(retranslate()));
    for(QString path : engine.importPathList())
    {
        qDebug() << path;
    }
    //engine.setMinimumSize({ 900, 600 });
    //engine.resize(900, 600);
    //engine.moveToScreenCenter();

    const QUrl mainQmlUrl(QStringLiteral("qrc:///main.qml"));
    const QMetaObject::Connection connection = QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [&mainQmlUrl, &connection](QObject *object, const QUrl &url) {
            if (url != mainQmlUrl) {
                return;
            }
            if (!object) {
                QGuiApplication::exit(-1);
            } else {
                QObject::disconnect(connection);
            }
        },
        Qt::QueuedConnection);

    engine.load(mainQmlUrl);



    return app.exec();
}
