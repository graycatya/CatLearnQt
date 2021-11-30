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

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void InitFrameless();

    void PaintShadow(QPainter *painter, QColor shadowcolor, int shadowwidth, qreal radius);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
