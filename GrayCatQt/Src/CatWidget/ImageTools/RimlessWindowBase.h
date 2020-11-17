#ifndef RIMLESSWINDOWBASE_H
#define RIMLESSWINDOWBASE_H

#include <QWidget>

class ProcessObject;

class RimlessWindowBase : public QWidget
{
    Q_OBJECT
public:
    explicit RimlessWindowBase(QWidget *parent = nullptr);
    ~RimlessWindowBase();

private:
    void InitProperty();
    bool ZoomIsInArea(QRect rect, QPoint pos);
    void SetZoomGeometry(int x, int y, int width, int height);

protected:
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void showEvent(QShowEvent *) override;
    void resizeEvent(QResizeEvent *event) override;
    void moveEvent(QMoveEvent *event) override;

private:

    QRect m_pZoom_Left_Top;
    QRect m_pZoom_Right_Top;

    QRect m_pZoom_Left_Bottom;
    QRect m_pZoom_Right_Bottom;

    QRect m_pZoom_Top;
    QRect m_pZoom_Left;
    QRect m_pZoom_Right;
    QRect m_pZoom_Bottom;

    QPoint m_qMovePos; // 坐标缓存

    ProcessObject *m_pScreen;  // 处理屏幕的对象

};

#endif // RIMLESSWINDOWBASE_H
