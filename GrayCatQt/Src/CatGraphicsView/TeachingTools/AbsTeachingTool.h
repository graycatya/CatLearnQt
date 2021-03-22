#ifndef ABSTEAHINGTOOL_H
#define ABSTEAHINGTOOL_H

#include <QObject>
#include <QApplication>
#include <QColor>
#include <QRectF>
#include <functional>

class QGraphicsSvgItem;
class QGraphicsView;
class QGraphicsScene;

typedef std::function<QGraphicsView*(QGraphicsScene*)> CurrentViewFunc;

class AbsTeachingTool : public QObject
{
    Q_OBJECT
    Q_ENUMS(TEAHINGTOOLSTATE)
public:

    enum TEAHINGTOOLSTATE {
        TEAHINGTOOL_STATE_NONE,             // 教具状态(无状态)
        TEAHINGTOOL_STATE_MOVE,             // 教具状态(移动)
        TEAHINGTOOL_STATE_RESIZE_ONE,       // 教具状态(改变大小-1)
        TEAHINGTOOL_STATE_RESIZE_TWO,       // 教具状态(改变大小-2)
        TEAHINGTOOL_STATE_RESIZE_THREE,     // 教具状态(改变大小-3)
        TEANINGTOOL_STATE_RESIZE_FOUR,      // 教具状态(改变大小-4)
        TEAHINGTOOL_STATE_ROTATE,           // 教具状态(旋转)
        TEAHINGTOOL_STATE_CLOSE,            // 教具状态(关闭)
        TEAHINGTOOL_STATE_REST,             // 教具状态(复位)
        TEAHINGTOOL_STATE_PEN,              // 教具状态(画图状态,画线)
        TEAHINGTOOL_STATE_DORMANCY          // 启动该状态为不响应任何鼠标事件
    };

    AbsTeachingTool() {
        m_yState = TEAHINGTOOL_STATE_NONE;
        SetRect(QRectF(0,0,0,0));
        SetMinRect(QRectF(0,0,0,0));
        SetMaxRect(QRectF(0,0,0,0));
        PenWidthF = 1;
        CurrentView = nullptr;
    }

    ~AbsTeachingTool() {}

    inline QString CurrentPath( void ) const {
        return QCoreApplication::applicationDirPath();
    }

    inline void SetRect(QRectF rect) {
        m_yRectF = rect;
    }

    inline QRectF Rect( void ) const {
        return m_yRectF;
    }

    inline void SetMinRect(QRectF rect) {
        m_yMinRectF = rect;
    }

    inline QRectF MinRect( void ) const {
        return m_yMinRectF;
    }

    inline void SetMaxRect(QRectF rect) {
        m_yMaxRectF = rect;
    }

    inline QRectF MaxRect( void ) const {
        return m_yMaxRectF;
    }

    inline void SetPressPos(QPointF pos) {
        m_yPressPos = pos;
    }

    inline QPointF PressPos( void ) const {
        return m_yPressPos;
    }

    inline void SetOriginPos(QPointF pos) {
        m_yOriginPos = pos;
    }

    inline QPointF OriginPos( void ) const {
        return m_yOriginPos;
    }

    inline void SetPenState(qreal penwidth) {
        PenWidthF = penwidth;
        m_yState = TEAHINGTOOL_STATE_PEN;
    }

    inline void SetPenState(int penwidth) {
        PenWidthF = static_cast<qreal>(penwidth);
        m_yState = TEAHINGTOOL_STATE_PEN;
    }

    inline void SetState( TEAHINGTOOLSTATE state ) {
        m_yState = state;
    }

    inline TEAHINGTOOLSTATE GetState( void ) const {
        return m_yState;
    }

    inline void SetCurrentView( CurrentViewFunc func )
    {
        CurrentView = func;
    }

    inline void SetPenWidth(qreal penwidth) {
        PenWidthF = penwidth;
    }

    inline qreal PenWidth( void ) const {
        return PenWidthF;
    }

protected:
    virtual void InitProperty( void ) = 0;
    virtual void UpdateResizeCursor( void ) = 0;
    virtual void SetCursor(QCursor cursor) = 0;

    CurrentViewFunc CurrentView;

signals:
    // 控件关闭信号
    void Closeed();
    // 鼠标移入信号
    void HoverEntered();
    // 鼠标移出信号
    void HoverLeaveed();
    // 画线起始点
    void LineStartPos(QPointF);
    // 画线更新结束点
    void LineUpdatePos(QPointF);
    // 退出画线
    void LineEnd();
    // 画圆起始点
    void ArcStartPos(QPointF);
    // 画圆更新结束点
    void ArcUpdatePos(QPointF);
    // 退出画圆
    void ArcEndPos();
    /**
     * @brief ArcStart 开始画弧
     * @param QRectF
     *
     *      QRectF(const QRect &rectangle)
     *      QRectF(qreal x, qreal y, qreal width, qreal height)
     *      QRectF(const QPointF &topLeft, const QPointF &bottomRight)
     *      QRectF(const QPointF &topLeft, const QSizeF &size)
     *
     *      本接口与drawArc一样
     * @param startAngle
     *        范围: 0 --- 360
     */
    void ArcStart(QRectF, qreal startAngle);

    /**
     * @brief ArcUpdate 更新圆弧的角度
     * @param updateAngle
     *        范围: -720 --- 720
     *        startAngle+updateAngle 为最终旋转后的角度
     */
    void ArcUpdate(qreal updateAngle);
    /**
     * @brief ArcEnd 退出画圆弧
     */
    void ArcEnd();

private:
    TEAHINGTOOLSTATE m_yState;

    QRectF m_yRectF;
    QRectF m_yMinRectF;
    QRectF m_yMaxRectF;

    QPointF m_yPressPos;
    QPointF m_yOriginPos;   // 原点坐标

    qreal PenWidthF;




};

#endif // ABSTEAHINGTOOL_H
