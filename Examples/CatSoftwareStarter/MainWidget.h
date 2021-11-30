#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>


namespace Ui {
class MainWidget;
}

#ifdef Q_OS_WIN
#include "CatFrameless/CatFramelessWidget.h"
class MainWidget : public CatFramelessWidget
#else
#include "CatFrameless/CatFramelessMainWindow.h"
class MainWidget : public CatFramelessMainWindow
#endif
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    void InitFrameless();

private:
    Ui::MainWidget *ui;
};

#endif // MAINWIDGET_H
