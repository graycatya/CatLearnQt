#ifndef TEAHINGTOOLPROTRACTOR_H
#define TEAHINGTOOLPROTRACTOR_H

#include "AbsTeachingTool.h"
#include <QGraphicsEllipseItem>

class ProtractorAngle;

class TeachingToolProtractor : public AbsTeachingTool, public QGraphicsEllipseItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    TeachingToolProtractor();
    ~TeachingToolProtractor();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    QPainterPath shape() const;

    void SetCloseButtonSvg(QString svg);
    void SetResizeButtonSvg(QString svg);
    void SetRotateButtonSvg(QString svg);
    void SetRestButtonSvg(QString svg);

    void SetProtractorBackgroundColor(QColor color);
    void SetProtractorBorderColor(QColor color);
    void SetProtractorTextColor(QColor color);
    void SetProtractorScaleColor(QColor color);
    void SetProtractorAxleColor(QColor color);

private:
    void InitProperty( void );

    QRectF CloseButtonRect() const;
    QRectF ResizeButtonRect() const;
    QRectF RotateButtonRect() const;
    QRectF RestButtonRect() const;

    void UpdateResizeCursor();

    void SetCursor(QCursor cursor);

    void PaintBackground(QPainter *painter);

    void PaintScale(QPainter *painter);

    void PaintProtractorAxis(QPainter *painter);

    void PaintButton();

    QPainterPath ProtractorBackgroundPath( void ) const;

    inline qreal radius () const{return rect().height() / 2 - 20;}

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
    QString RotateButtonSvg;
    QString RestButtonSvg;

    QCursor RotateCursor;           // 旋转时鼠标显示的图标
    QCursor ResizeCursor;           // 改变大小显示的图标
    QCursor MoveCursor;             // 移动时显示的图标
    QCursor CloseCursor;            // 关闭鼠标的图标

    QGraphicsSvgItem *m_pCloseButton = nullptr;           // 关闭按钮
    QGraphicsSvgItem *m_pResizeButton = nullptr;          // 改变大小按钮
    QGraphicsSvgItem *m_pRotateButton = nullptr;          // 旋转按钮
    QGraphicsSvgItem *m_pRestButton = nullptr;            // 复位按钮

    // 量角器字体颜色
    QColor ProtractorTextColor;

    // 量角器刻度颜色
    QColor ProtractorScaleColor;

    // 量角器量角轴颜色
    QColor ProtractorAxleColor;

    // 量角器主体颜色
    QColor ProtractorBackgroundColor;

    // 量角器边框颜色
    QColor ProtractorBorderColor;

    // 量角器边距
    qreal ProtractorBorderWidth;

    // 量角器默认大小
    static const QRectF sDefaultRect;

    // 量角轴角度
    qreal mCurrentAngle;
    // 比例系数
    qreal mScaleFactor;

    // 量角按钮
    ProtractorAngle *m_pProtractorAngle = nullptr;
};

#endif // TEAHINGTOOLPROTRACTOR_H
