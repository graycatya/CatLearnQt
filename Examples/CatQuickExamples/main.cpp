#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QQmlContext>
#ifdef Q_CC_MSVC
#include "CatFrameless/CatFrameLessView.h"
#endif
#include "QrenCode/QuickQrenCodeParentItem.h"
#include <QmlCatLog.h>
#include "CatConfig.h"


int main(int argc, char *argv[])
{
    //QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QMLCATLOG::CatLog *catlog = QMLCATLOG::CatLog::Instance();
    CatConfig *catconfig = CatConfig::Instance();
    QGuiApplication app(argc, argv);

    qmlRegisterType<QuickQrenCodeParentItem>("QParentQrenCode", 1, 0, "ParentQrenCode");
#ifdef QT_OS_WIN10
    CatFrameLessView view;

    //view.engine()->addImportPath(TaoQuickImportPath);
    view.engine()->addImportPath(GrayCatQtQuickImportPath);
    view.engine()->rootContext()->setContextProperty("view", &view);
    view.engine()->rootContext()->setContextProperty("catLog", catlog);
    view.engine()->rootContext()->setContextProperty("catconfig", catconfig);
    for(QString path : view.engine()->importPathList())
    {
        qDebug() << path;
    }
    view.setMinimumSize({ 800, 600 });
    view.resize(800, 600);
    view.moveToScreenCenter();

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    view.setSource(url);
    view.show();
#else
    QQmlApplicationEngine engine;
    engine.addImportPath(GrayCatQtQuickImportPath);
    engine.rootContext()->setContextProperty("catLog", catlog);
    engine.rootContext()->setContextProperty("catconfig", catconfig);
    for(QString path : engine.importPathList())
    {
        qDebug() << path;
    }
    engine.load( QUrl( "qrc:/generalmain.qml" ) );
#endif

    return app.exec();
}
