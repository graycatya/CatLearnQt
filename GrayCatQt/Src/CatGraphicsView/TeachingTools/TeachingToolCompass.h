#ifndef TEAHINGTOOLCOMPASS_H
#define TEAHINGTOOLCOMPASS_H

#include "AbsTeachingTool.h"
#include <QGraphicsItem>

class TeachingToolCompass : public AbsTeachingTool, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    TeachingToolCompass();
    ~TeachingToolCompass();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    QPainterPath shape() const;

    void SetCloseButtonSvg(QString svg);
    void SetResizeButtonSvg(QString svg);

    void SetCompassesSharpColor(QColor color);
    void SetCompassesSharpRectangleColor(QColor color);
    void SetCompassesPenPointColor(QColor color);
    void SetCompassesPenPointRectangleColor(QColor color);
    void SetCompassesSpindleRectangleColor(QColor color);
    void SetCompassesSpindleRoundnessColor(QColor color);
    void SetCompassesOutriggerColor(QColor color);
    void SetCompassesTextColor(QColor color);
    void SetCompassesBorderColor(QColor color);

private:

    void InitProperty();
    void UpdateResizeCursor();
    void UpdatePenCircleCursor();

    void SetCursor(QCursor cursor);

    // 画圆规尖
    void PaintCompassesSharp(QPainter *painter);
    // 圆规尖Rectangle 连接处矩形
    void PaintCompassesSharpRectangle(QPainter *painter);
    // 圆规支腿
    void PaintCompassesOutrigger(QPainter *painter);
    // 圆规转轴
    void PaintCompassesSpindle(QPainter *painter);
    // 笔尖Rectangle 连接处矩形
    void PaintCompassesPenPointRectangle(QPainter *painter);
    // 笔尖
    void PaintCompassesPenPoint(QPainter *painter);
    // 画圆规长度
    void PaintCompassesLine(QPainter *painter);

    void PaintButton( void );

    void rotateAroundNeedle(qreal angle);
    qreal angleInDegrees() const;



    QRectF CloseButtonRect() const;
    QRectF ResizeButtonRect() const;

    QPainterPath CompassesSharpPath( void ) const;
    QPainterPath CompassesSharpRectanglePath( void ) const;
    QPainterPath CompassesOutriggerPath( void ) const;
    QPainterPath CompassesSpindleRectanglePath( void ) const;
    QPainterPath CompassesSpindleCirclePath( void ) const;
    QPainterPath CompassesPenPointRectanglePath( void ) const;
    QPainterPath CompassesPenPointPath( void ) const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private:
    // svg文件
    QString CloseButtonSvg;
    QString ResizeButtonSvg;

    QGraphicsSvgItem *m_pCloseButton;           // 关闭按钮
    QGraphicsSvgItem *m_pResizeButton;          // 改变大小按钮

    QColor CompassesSharpColor;                 // 圆规尖颜色
    QColor CompassesSharpRectangleColor;        // 圆规尖矩形颜色
    QColor CompassesPenPointColor;              // 圆规笔尖颜色
    QColor CompassesPenPointRectangleColor;     // 圆规笔尖矩形颜色
    QColor CompassesSpindleRectangleColor;      // 圆规转轴矩形颜色
    QColor CompassesSpindleRoundnessColor;      // 圆规转轴圆形颜色
    QColor CompassesOutriggerColor;             // 圆规身体颜色
    QColor CompassesTextColor;                  // 圆规字体颜色
    QColor CompassesBorderColor;                // 圆规边颜色

    QCursor RotateCursor;                       // 旋转时鼠标显示的图标
    QCursor PenCircleCursor;                    // 画圆时，显示的鼠标提示
    QCursor ResizeCursor;                       // 改变大小显示的图标
    QCursor MoveCursor;                         // 移动时显示的图标
    QCursor CloseCursor;                        // 关闭鼠标的图标

    QRectF CompassesSharpRect;                  // 圆规尖大小
    QRectF CompassesSharpRectangleRect;         // 圆规尖连接处矩形大小
    QRectF CompassesOutriggerRect;              // 圆规支腿大小
    QRectF CompassesSpindleRect;                // 圆规转轴大小
    QRectF CompassesPenPointRectangleRect;      // 圆规笔尖连接处矩形大小
    QRectF CompassesPenPointRect;               // 圆规笔尖大小

    qreal CompassesSharpRectangleBorderRadius;
    qreal CompassesOutriggerBorderRadius;
    qreal CompassesSpindleBorderRadius;
    qreal CompassesPenPointRectangleBorderRadius;

    qreal SpanAngleInDegrees;

    qreal CurrentAngle;

};

#endif // TEAHINGTOOLCOMPASS_H
