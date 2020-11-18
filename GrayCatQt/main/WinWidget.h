#ifndef WINWIDGET_H
#define WINWIDGET_H

#include <QWidget>

namespace Ui {
class WinWidget;
}

class WinWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WinWidget(QWidget *parent = nullptr);
    ~WinWidget();

private:
    Ui::WinWidget *ui;
};

#endif // WINWIDGET_H
