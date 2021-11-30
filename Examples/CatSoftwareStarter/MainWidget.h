#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "CatFrameless/CatFramelessWidget.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public CatFramelessWidget
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
