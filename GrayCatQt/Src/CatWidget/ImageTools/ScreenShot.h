#ifndef SCREENSHOT_H
#define SCREENSHOT_H
#include "ImageToolBase.h"

class ScreenShot : public ImageToolBase
{
    Q_OBJECT
public:
    explicit ScreenShot(QWidget *parent = nullptr);
    ~ScreenShot();

private:
    void InitUi() override;
    void InitProperty() override;

    void SetZoomVisible(bool visible);
    void SetZoomGeometry(int x, int y, int width, int height);

    bool ZoomIsInArea(QWidget *Zoom, QPoint pos);

    void Save();

protected:
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void paintEvent(QPaintEvent *) override;
    void showEvent(QShowEvent *) override;
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    QWidget *m_pZoom_Top;
    QWidget *m_pZoom_Bottom;
    QWidget *m_pZoom_Left;
    QWidget *m_pZoom_Right;
    QWidget *m_pZoom_Left_Top;
    QWidget *m_pZoom_Right_Top;
    QWidget *m_pZoom_Left_Bottom;
    QWidget *m_pZoom_Right_Bottom;

    bool m_pMousePress;

};

#endif // SCREENSHOT_H
