#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    // 设置全局字体，用于解决Qt for WebAssembly中文显示异常
    int fontId = QFontDatabase::addApplicationFont(QStringLiteral(":/font/SIMYOU.TTF"));

    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);

    qDebug()<<"fontfamilies:"<<fontFamilies;
    if (fontFamilies.size() > 0)
    {
        QFont font;
        font.setFamily(fontFamilies[0]);//设置全局字体
        app.setFont(font);
    }
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/RunMain.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
