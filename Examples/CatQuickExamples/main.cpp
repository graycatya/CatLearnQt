#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include "CatFrameless/CatFrameLessView.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
#ifdef QT_OS_WIN7
    QQmlApplicationEngine engine;
    engine.addImportPath(GrayCatQtQuickImportPath);
    engine.load( QUrl( "qrc:/win7main.qml" ) );
#else
    CatFrameLessView view;
    //view.engine()->addImportPath(TaoQuickImportPath);
    view.engine()->addImportPath(GrayCatQtQuickImportPath);

    for(QString path : view.engine()->importPathList())
        qDebug() << path;
    //view.setMinimumSize({ 800, 600 });
    view.resize(800, 600);
    view.moveToScreenCenter();

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    view.setSource(url);
    view.show();
#endif

    return app.exec();
}
