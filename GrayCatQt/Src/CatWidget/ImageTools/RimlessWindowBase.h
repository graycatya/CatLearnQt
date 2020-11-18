#ifndef RIMLESSWINDOWBASE_H
#define RIMLESSWINDOWBASE_H

#include <QWidget>

class ProcessObject;

class RimlessWindowBase : public QWidget
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
    explicit RimlessWindowBase(QWidget *parent = nullptr);
    ~RimlessWindowBase();

private:
    void InitProperty();
    bool ZoomIsInArea(QRect rect, QPoint pos);
    void SetZoomGeometry(int x, int y, int width, int height);

protected:
    void SetMoveRect(QRect rect);
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void showEvent(QShowEvent *) override;
    void resizeEvent(QResizeEvent *event) override;
    void moveEvent(QMoveEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    QRect m_pZoom_Left_Top;
    QRect m_pZoom_Right_Top;

    QRect m_pZoom_Left_Bottom;
    QRect m_pZoom_Right_Bottom;

    QRect m_pZoom_Top;
    QRect m_pZoom_Left;
    QRect m_pZoom_Right;
    QRect m_pZoom_Bottom;

    QRect m_pMove_Rect;

    bool m_bMousePress;

    ProcessObject *m_pScreen;  // 处理屏幕的对象

    QPoint m_qMovePos; // 坐标缓存

    CURSORSTATE m_qCursorState;

};

#endif // RIMLESSWINDOWBASE_H
