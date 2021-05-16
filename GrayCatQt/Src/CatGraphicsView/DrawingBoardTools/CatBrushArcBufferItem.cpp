#include "CatBrushArcBufferItem.h"
#include <QPainter>

CatBrushArcBufferItem::CatBrushArcBufferItem(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    m_yBackGround = "transparent";
    m_yBroad = 0;
    m_yRect = {0,0,0,0};
    m_yStartAngle = 0;
    m_yUpdateAngle = 0;
    this->setZValue(0);
}

CatBrushArcBufferItem::~CatBrushArcBufferItem()
{

}

void CatBrushArcBufferItem::SetProperty(QColor background, qreal broad)
{
    m_yBackGround = background;
    m_yBroad = broad;
}

void CatBrushArcBufferItem::ArcStart(QRectF rect, qreal startAngle)
{
    m_yRect = rect;
    m_yStartAngle = startAngle;
}

void CatBrushArcBufferItem::ArcUpdate(qreal updateAngle)
{
    m_yUpdateAngle = updateAngle;
    this->update();
}

void CatBrushArcBufferItem::ArcEnd()
{

}

QRectF CatBrushArcBufferItem::boundingRect() const
{
    return m_yRect;
}

void CatBrushArcBufferItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // 打开抗锯齿
    painter->setRenderHint(QPainter::Antialiasing, true);
    // 平滑的像素图转换算法
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    // 指示引擎应尽可能消除文本的别名
    painter->setRenderHint(QPainter::TextAntialiasing, true);
    QPen pen = painter->pen();
    pen.setWidth(m_yBroad);
    pen.setColor(m_yBackGround);
    //setPen(QPen(Qt::red, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    painter->setPen(pen);
    painter->drawArc(m_yRect, m_yStartAngle, m_yUpdateAngle);
}

QPainterPath CatBrushArcBufferItem::shape() const
{
    QPainterPath path;
    path.addRect(m_yRect);
    return path;
}
