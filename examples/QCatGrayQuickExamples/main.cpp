#include <QQmlApplicationEngine>
#include <QDebug>
#include <QVariant>
//#include <QQmlContext>
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
#ifdef QT_WEBENGINE_LIB
#include <QtWebEngine>
#include <QtWebView>
#include <QWebChannel>
#include <QWebSocketServer>
#endif
#else
#ifdef QT_WEBENGINEQUICK_LIB
#include <QtWebEngineQuick>
#include <QtWebView>
#include <QWebChannel>
#include <QWebSocketServer>
#endif
#endif
#include "CatConfig.h"

#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickView>
#include <QtQuickControls2/qquickstyle.h>

#include "QmlConfig.h"



int main(int argc, char *argv[])
{
    //QGuiApplication
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
#ifdef QT_WEBENGINE_LIB
    QtWebEngine::initialize();
#endif
#else
#ifdef QT_WEBENGINEQUICK_LIB
    QtWebEngineQuick::initialize();
#endif
#endif
    QCoreApplication::setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::Round);
#endif



    QGuiApplication app(argc, argv);

    app.setOrganizationName("GrayCatYa");
    app.setOrganizationDomain("graycatya.com");
    app.setApplicationName(APP_NAME);

#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
    QQuickStyle::setStyle(QStringLiteral("Basic"));
#else
    QQuickStyle::setStyle(QStringLiteral("Default"));
#endif
#ifndef WEBASSEMBLY
    CatConfig *catconfig = CatConfig::Instance();
    catconfig->InitConfig();



#endif
    QmlConfig::moduleRegister();


    QQmlApplicationEngine engine;
    //engine.rootContext()->setContextProperty("view", &view);
    engine.rootContext()->setContextProperty("catconfig", catconfig);
    engine.rootContext()->setContextProperty("qtversion", QString(qVersion()));

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
