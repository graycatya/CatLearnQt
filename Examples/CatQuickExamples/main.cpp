#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "CatFrameless/CatFrameLessView.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    CatFrameLessView view;
    view.engine()->addImportPath(GrayCatQtQuickImportPath);
    qDebug() << "GrayCatQtQuickImportPath: " << GrayCatQtQuickImportPath;
    view.setMinimumSize({ 800, 600 });
    view.resize(1440, 960);
    view.moveToScreenCenter();

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    view.setSource(url);
    view.show();

    return app.exec();
}
