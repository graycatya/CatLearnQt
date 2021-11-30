#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "CatFrameless/CatFramelessMainWindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public CatFramelessMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void InitFrameless();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
