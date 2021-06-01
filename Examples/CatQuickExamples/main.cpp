#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
//#include "CatFrameless/CatFrameLessView.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
/*
    CatFrameLessView view;
    //view.engine()->addImportPath(TaoQuickImportPath);
    view.engine()->addImportPath(GrayCatQtQuickImportPath);
    //qDebug() << "TaoQuickImportPath: " << TaoQuickImportPath;
    qDebug() << "GrayCatQtQuickImportPath: " << GrayCatQtQuickImportPath;

    for(QString path : view.engine()->importPathList())
        qDebug() << path;
    //view.setMinimumSize({ 800, 600 });
    view.resize(800, 600);
    view.moveToScreenCenter();

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    view.setSource(url);
    view.show();
*/

    QQmlApplicationEngine engine;
    engine.addImportPath(GrayCatQtQuickImportPath);
    /*engine.addImportPath(TaoQuickImportPath);
    qDebug() << "TaoQuickImportPath: " << TaoQuickImportPath;*/
    engine.load( QUrl( "qrc:/win7main.qml" ) );
    return app.exec();
}
