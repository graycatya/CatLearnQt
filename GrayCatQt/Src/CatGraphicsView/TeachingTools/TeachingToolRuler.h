#ifndef TEAHINGTOOLRULER_H
#define TEAHINGTOOLRULER_H

#include "AbsTeachingTool.h"
#include <QGraphicsItem>

class TeachingToolRuler : public AbsTeachingTool, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    TeachingToolRuler();
    ~TeachingToolRuler();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    QPainterPath shape() const;

    void SetRulerBorderRadius(int radius);
    void SetRulerBackgroundColor(QColor color);
    void SetRulerBorderColor(QColor color);
    void SetRulerScaleTextColor(QColor color);
    void SetRulerScaleColor(QColor color);
    void SetRulerRotateColor(QColor color);

    void SetCloseButtonSvg(QString svg);
    void SetResizeButtonSvg(QString svg);
    void SetRotateButtonSvg(QString svg);

private:
    enum DRAWLINE {
        TOP,
        BOTTOM
    };

    void InitProperty();

    void UpdateResizeCursor();

    void SetCursor(QCursor cursor);

    QRectF CloseButtonRect() const;
    QRectF ResizeButtonRect() const;
    QRectF RotateButtonRect() const;

    void PaintBody(QPainter *painter);
    void PaintButton( void );
    void PaintScale(QPainter *painter);
    void PaintRotate(QPainter *painter);

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

    QGraphicsSvgItem *m_pCloseButton = nullptr;           // 关闭按钮
    QGraphicsSvgItem *m_pResizeButton = nullptr;          // 改变大小按钮
    QGraphicsSvgItem *m_pRotateButton = nullptr;          // 旋转按钮

    // 颜色样式
    int RulerBorderRadius;
    QColor RulerBackgroundColor;
    QColor RulerBorderColor;
    QColor RulerScaleTextColor;
    QColor RulerScaleColor;
    QColor RulerRotateColor;

    QCursor RotateCursor;           // 旋转时鼠标显示的图标
    QCursor DrawLineRulerCursor;    // 与白板交互时绘制功能，鼠标显示图标
    QCursor ResizeCursor;           // 改变大小显示的图标
    QCursor MoveCursor;             // 移动时显示的图标
    QCursor CloseCursor;            // 关闭鼠标的图标


    DRAWLINE DrawLineState;

};

#endif // TEAHINGTOOLRULER_H
