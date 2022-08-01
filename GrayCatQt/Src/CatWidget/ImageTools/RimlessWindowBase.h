#ifndef RIMLESSWINDOWBASE_H
#define RIMLESSWINDOWBASE_H

#include <QWidget>

class ProcessObject;

class RimlessWindowBase : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor ShadowColor READ GetShadowColor WRITE SetShadowColor)
    Q_PROPERTY(int ShadowWeight READ GetShadowWeight WRITE SetShadowWeight)
public:
    enum CURSORSTATE {
        NONE,
        TOPLEFT,
        TOPRIGHT,
        BOTTOMLEFT,
        BOTTOMRIGHT
    };
    explicit RimlessWindowBase(QWidget *parent = nullptr, bool shadow = false);
    ~RimlessWindowBase();

    inline QColor GetShadowColor( void ) const
    {
        return ShadowColor;
    }

    inline int GetShadowWeight( void ) const
    {
        return ShadowWeight;
    }

private:
    void InitProperty();
    bool ZoomIsInArea(QRect rect, QPoint pos);
    void SetZoomGeometry(int x, int y, int width, int height);

#ifdef Q_OS_LINUX
#ifndef Q_OS_ANDROID
    void LinuxMoveWidget( int type, QString event = "_NET_WM_MOVERESIZE");
#endif
#endif

protected:
    void SetProcessGeometry(int x, int y, int width, int height);

protected:
    void SetMoveRect(QRect rect);
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void showEvent(QShowEvent *) override;
    void resizeEvent(QResizeEvent *event) override;
    void moveEvent(QMoveEvent *event) override;
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
    void enterEvent(QEnterEvent *event) override;
#else
    void enterEvent(QEvent *event) override;
#endif
    void leaveEvent(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

signals:
    void moveEvented();
    void mouseMoveed(QPoint pos);

public slots:
    void SetShadowColor(QColor color);
    void SetShadowWeight(int weight);

protected:
    bool m_bMousePress;

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

    ProcessObject *m_pScreen;  // 处理屏幕的对象

    QPoint m_qMovePos; // 坐标缓存

    CURSORSTATE m_qCursorState;

    QRect m_pLast_Rect;

    bool m_bShadow;

    // 阴影属性
    QColor ShadowColor;
    int ShadowWeight;


};

#endif // RIMLESSWINDOWBASE_H
