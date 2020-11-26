#ifndef WINWIDGET_H
#define WINWIDGET_H

#include "RimlessWindowBase.h"

namespace Ui {
class WinWidget;
}

class WinWidget : public
#ifdef Q_OS_LINUX
    QWidget
#else
    RimlessWindowBase
#endif
{
    Q_OBJECT

public:
    enum CURSORSTATE {
        NONE,
        TOPLEFT,
        TOPRIGHT,
        BOTTOMLEFT,
        BOTTOMRIGHT
    };
    explicit WinWidget(QWidget *parent = nullptr);
    ~WinWidget();

private:
    void InitUi();
    void InitProperty();

protected:
    bool eventFilter(QObject *watched, QEvent *event);



private:
    Ui::WinWidget *ui;


};

#endif // WINWIDGET_H
