#ifndef CATGIFTOOL_H
#define CATGIFTOOL_H
#include "ImageToolBase.h"


class GifButtonWidget;

class CatGifTool : public ImageToolBase
{
    Q_OBJECT
public:
    CatGifTool(QWidget *parent = nullptr);
    ~CatGifTool();
    void SetGeometry(int x, int y, int width, int height);

    void SetMoveState(QString state);


private:
    void InitUi() override;
    void InitProperty() override;

    void SetZoomVisible(bool visible);
    void SetMoveWidgetVisible(bool visible);
    void SetZoomGeometry(int x, int y, int width, int height);



    bool ZoomIsInArea(QWidget *Zoom, QPoint pos);

protected:
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void paintEvent(QPaintEvent *) override;
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
    void enterEvent(QEnterEvent *event) override;
#else
    void enterEvent(QEvent *event) override;
#endif
    //void leaveEvent(QEvent *event) override;
    //void showEvent(QShowEvent *) override;

signals:
    void gifgeometry(int, int, int, int);

public slots:
    void On_Move(bool move);
    void On_Show(bool show);
    void On_Start(bool start);


private:
    bool m_bMove;
    bool m_bStart;
    bool m_bShow;
    bool m_bEnter;
    bool m_bResize;
    QWidget *m_pZoom_Top;
    QWidget *m_pZoom_Bottom;
    QWidget *m_pZoom_Left;
    QWidget *m_pZoom_Right;
    QWidget *m_pZoom_Left_Top;
    QWidget *m_pZoom_Right_Top;
    QWidget *m_pZoom_Left_Bottom;
    QWidget *m_pZoom_Right_Bottom;
    QWidget *m_pMoveWidget;
    GifButtonWidget *m_pGifButtonWidget;

};

#endif // CATGIFTOOL_H
