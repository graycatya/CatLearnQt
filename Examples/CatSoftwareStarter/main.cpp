#include <QApplication>
#include "MainWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWidget widget;
    widget.show();

    return a.exec();
}
