#ifndef WINMAINWIDGET_H
#define WINMAINWIDGET_H

#include <QMainWindow>
#include "RimlessWindowBase.h"
#ifdef Q_OS_WIN
#include "CatFramelessWidget.h"
#include "CatFrameLessMainView.h"
#endif
#include <QHash>

class QPushButton;
class ListiongOptions;
class CatDrawingBoard;
class CatAbout;
class CatSettings;
class CatWidget;
class CatQuickWidget;

namespace Ui {
class WinMainWidget;
}

class WinMainWidget : public
#if defined(Q_OS_LINUX) || defined(Q_OS_MAC)
    QMainWindow
#else
    CatFrameLessMainView
#endif
{
    Q_OBJECT

public:
    explicit WinMainWidget(QWidget *parent = nullptr);
    ~WinMainWidget();

private:
    void InitUi();
    void InitProperty();
    void InitConnect();
    void InitButtonList();

    void SetZoomButtonState(QString state);

    void SetWindowZoom();

    void SetTitle(QString state = "");

    void UpdateStyle();

    void retranslateUi();

protected:
    bool eventFilter(QObject *watched, QEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void changeEvent(QEvent *event);
    void closeEvent(QCloseEvent *event);

signals:
    void Closeed();

private slots:
    void On_ButtonFunc(int id);

private:
    Ui::WinMainWidget *ui;
    ListiongOptions *m_pListiongOptions;
    QHash<QString, QPushButton*> m_pButtons;

    CatDrawingBoard *m_pCatDrawingBoard;
    CatAbout *m_pCatAbout;
    CatSettings *m_pCatSettings;
    CatWidget *m_pCatWidget;
    CatQuickWidget *m_pCatQuickWidget;

    bool m_bFullScreen;
    bool m_bTopWidget;
    QRect m_pLastRect;

    // 阴影属性
    QColor ShadowColor;
    int ShadowWeight;

};

#endif // WINMAINWIDGET_H
