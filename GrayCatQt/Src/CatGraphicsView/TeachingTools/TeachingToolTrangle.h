#ifndef TEAHINGTOOLTRANGLE_H
#define TEAHINGTOOLTRANGLE_H

#include "AbsTeachingTool.h"
#include <QGraphicsPolygonItem>

class TeachingToolTrangle : public AbsTeachingTool, public QGraphicsPolygonItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    TeachingToolTrangle();
    ~TeachingToolTrangle();

    enum TRANGLEORIENTATION {
        BottomLeft = 0,
        BottomRight,
        TopLeft,
        TopRight
    };

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    QPainterPath shape() const;

    void SetCloseButtonSvg(QString svg);
    void SetRotateButtonSvg(QString svg);
    void SetFlipHorizontalButtonSvg(QString svg);
    void SetFlipVerticalButtonSvg(QString svg);

    void SetTrangleBorderColor(QColor color);
    void SetTrangleBackgroundColor(QColor color);
    void SetTrangleResizeButtonColor(QColor color);
    void SetTrangleScaleTextColor(QColor color);
    void SetTrangleScaleColor(QColor color);

    void Move(QPointF lastpot, QPointF currentpot);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    //void moveEvent(QGraphicsSceneMoveEvent *event);

private:
    void InitProperty();

    void UpdateResizeCursor();

    void SetCursor(QCursor cursor);

    void SetOrientation(TRANGLEORIENTATION orientation);

    void UpdateOriginPos();

    void UpdateResize1RectF(QPointF pos);
    void UpdateResize2RectF(QPointF pos);

    void CalculatePoints(const QRectF & r);

    QRectF CloseButtonRect() const;
    QRectF RotateButtonRect() const;
    QRectF FlipVerticalButtonRect() const;
    QRectF FlipHorizontalButtonRect() const;
    QPolygonF resize1Polygon() const;
    QPolygonF resize2Polygon() const;

    QCursor resizeCursor1() const;
    QCursor resizeCursor2() const;

    TRANGLEORIENTATION VerticalOrientation(TRANGLEORIENTATION Orientation);
    TRANGLEORIENTATION HorizontalOrientation(TRANGLEORIENTATION Orientation);

    QPointF rotationCenter() const;
    void rotateAroundCenter(qreal angles);
    void rotateAroundCenter(QTransform& transform, QPointF center);

    void paintGraduations(QPainter *painter);

    qreal angleInDegrees() const;

    QPointF UpdatePenPos(QGraphicsSceneMouseEvent *event);

private:
    // svg文件
    QString CloseButtonSvg;
    QString RotateButtonSvg;
    QString FlipHorizontalButtonSvg;
    QString FlipVerticalButtonSvg;

    QGraphicsSvgItem *m_pCloseButton = nullptr;           // 关闭按钮
    QGraphicsSvgItem *m_pRotateButton = nullptr;          // 旋转按钮
    QGraphicsSvgItem *m_pFlipHorizontalButton = nullptr;  // 水平翻转按钮
    QGraphicsSvgItem *m_pFlipVerticalButton = nullptr;    // 垂直翻转按钮

    QCursor RotateCursor;           // 旋转时鼠标显示的图标
    QCursor DrawLineRulerCursor;    // 与白板交互时绘制功能，鼠标显示图标
    QCursor MoveCursor;             // 移动时显示的图标
    QCursor CloseCursor;            // 关闭鼠标的图标
    QCursor mResizeCursor1;
    QCursor mResizeCursor2;

    // 颜色样式
    QColor TrangleBorderColor;          // 三角尺边框颜色
    QColor TrangleBackgroundColor;      // 三角尺背景颜色
    QColor TrangleResizeButtonColor;    // 三角尺改变大小按钮颜色
    QColor TrangleScaleTextColor;
    QColor TrangleScaleColor;

    qreal angle = 0;

    qreal m_yCurrentAngle = 0.0;

    QPointF A1, B1, C1, A2, B2, C2;

    qreal C;

    QRectF m_yLastRectF;

    bool mShouldPaintInnerTriangle;
    bool mShowResize1 = false;
    bool mShowResize2 = false;

    TRANGLEORIENTATION mOrientation;

    QPointF TopLeftOriginPos;
    QPointF BottomLeftOriginPos;
    QPointF TopRightOriginPos;
    QPointF BottomRightOriginPos;

    qreal deleteX;
    qreal LeftSide;
    qreal RightSide;

    qreal sPixelsPerCentimeter;
};

#endif // TEAHINGTOOLTRANGLE_H
