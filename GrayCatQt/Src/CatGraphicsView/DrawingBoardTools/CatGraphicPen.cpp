#include "CatGraphicPen.h"

#include <QPainter>

#include <QDebug>

CatGraphicPen::CatGraphicPen(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    InitProperty();
}

CatGraphicPen::~CatGraphicPen()
{

}

QRectF CatGraphicPen::boundingRect() const
{
    return GetBaseItemSize();
}

void CatGraphicPen::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setRenderHint(QPainter::Antialiasing, true);

    QPen pen;
    pen.setColor(Qt::gray);
    pen.setCapStyle(Qt::PenCapStyle::RoundCap);
    pen.setJoinStyle(Qt::PenJoinStyle::RoundJoin);

    painter->setCompositionMode(QPainter::CompositionMode_Source);
    painter->setPen(pen);
    painter->drawLines(m_pLines);
    painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
    //painter->drawPath(m_pBeziner);
    /*
    QPen pen;
    pen.setColor(Qt::gray);
    painter->setPen(pen);*/
    painter->drawRect(this->GetBaseItemSize());
    if(m_pLines.size() > 500)
    {

        painter->setCompositionMode(QPainter::CompositionMode_DestinationOut);
        painter->setPen(pen);
        painter->drawLines(m_pLines);
        painter->setCompositionMode(QPainter::CompositionMode_DestinationOver);
    }


    //painter->fillRect(QRectF(0,0,100,100), QBrush(Qt::gray));

}

QPainterPath CatGraphicPen::shape() const
{
    QPainterPath path;
    path.addRect(GetBaseItemSize());
    return path;
}

void CatGraphicPen::GraphicPenAddPoint(QPointF point)
{
    UpdateRectSize(point);

    if(m_pLines.isEmpty())
    {
        QPointF sp = point;
        QPointF ep = point;
        QPointF c1 = QPointF((sp.x() + ep.x()) / 2, sp.y());
        QPointF c2 = QPointF((sp.x() + ep.x()) / 2, ep.y());
        m_pBeziner.cubicTo(c1, c2, ep);
        m_pLines.push_back(QLineF(point, point));
    } else {
        QPointF sp = m_pLastPoint;
        QPointF ep = point;
        QPointF c1 = QPointF((sp.x() + ep.x()) / 2, sp.y());
        QPointF c2 = QPointF((sp.x() + ep.x()) / 2, ep.y());
        m_pBeziner.cubicTo(c1, c2, ep);
        m_pLines.push_back(QLineF(m_pLastPoint, point));
    }
    m_pLastPoint = point;
    update();
}

void CatGraphicPen::InitProperty()
{
    //setFlag(QGraphicsItem::ItemIsMovable, true);//可以拖动
    //setFlag(QGraphicsItem::ItemIsSelectable, true);//可以选中
    this->SetBaseItemSize(QRectF(0, 0, 0, 0));
}

void CatGraphicPen::UpdateRectSize(QPointF point)
{

    qreal left = this->GetBaseItemSize().left();
    qreal right = this->GetBaseItemSize().right();
    qreal top = this->GetBaseItemSize().top();
    qreal bottom = this->GetBaseItemSize().bottom();

    if(left == 0 && right == 0 && top == 0 && bottom == 0)
    {
        left = point.x();
        right = point.x();
        top = point.y();
        bottom = point.y();
    } else {

        if(point.x() < this->GetBaseItemSize().left())
        {
            left = point.x();
        }

        if(point.x() > this->GetBaseItemSize().right())
        {
            right = point.x();
        }

        if(point.y() < this->GetBaseItemSize().top())
        {
            top = point.y();
        }

        if(point.y() > this->GetBaseItemSize().bottom())
        {
            bottom = point.y();
        }

    }
    this->SetBaseItemSize(QRectF(left, top, right - left, bottom - top));
    //this->SetBaseItemSize(QRectF(point.x(), point.y(), 100, 100));
}

void CatGraphicPen::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
}

void CatGraphicPen::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
}

void CatGraphicPen::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
}
