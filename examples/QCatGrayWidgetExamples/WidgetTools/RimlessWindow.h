#ifndef RIMLESSWINDOW_H
#define RIMLESSWINDOW_H
#include "CatWidget/ImageTools/ImageToolBase.h"

class RimlessWindow : public ImageToolBase
{
    Q_OBJECT
public:
    explicit RimlessWindow(QWidget *parent = nullptr);
    ~RimlessWindow();

private:
    void InitUi() override;
    void InitProperty() override;

    void SetZoomVisible(bool visible);
    void SetZoomGeometry(int x, int y, int width, int height);

    bool ZoomIsInArea(QWidget *Zoom, QPoint pos);

protected:
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void paintEvent(QPaintEvent *) override;
    void showEvent(QShowEvent *) override;
    void resizeEvent(QResizeEvent *) override;
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

#endif // RIMLESSWINDOW_H
