#include "CatCanvasItem.h"
#include <QPainter>

#include <QDebug>

CatCanvasItem::CatCanvasItem(const QSizeF &size, QGraphicsObject *parent)
    : QGraphicsObject(parent)
    , m_ySize(size)
{
    InitProperty();
    InitCanvas();
}

CatCanvasItem::~CatCanvasItem()
{
    if(m_pRealPainter != nullptr)
    {
        delete m_pRealPainter;
        m_pRealPainter = nullptr;
    }
    if(m_pRealCancvas)
    {
        delete m_pRealCancvas;
        m_pRealCancvas = nullptr;
    }
}

void CatCanvasItem::DrawPress(int id, const QPointF &point)
{
    CatLineObject *LineObject = new CatLineObject(point);
    LineObject->addToPath(point, point);
    m_yLineObjects.insert(id, LineObject);
    m_pCatCanvasDoubleBuffering->DrawToBuffering(LineObject);
}

void CatCanvasItem::DrawMove(int id, const QPointF &lastPoint, const QPointF &curPoint)
{
    CatLineObject *object = m_yLineObjects.value(id, nullptr);
    if(object == nullptr)
    {
        return;
    }
    object->addToPath(lastPoint, curPoint);

    if(m_yCanvasMode == DrawMode)
    {
        DrawToReal(object);
        object->createNewPath();
    } else if(m_yCanvasMode == EraserMode)
    {
        DoErase(lastPoint, curPoint, 30);
    }
}

void CatCanvasItem::DrawRelease(int id, const QPointF &point)
{
    CatLineObject *object = m_yLineObjects.value(id, nullptr);
    if(object == nullptr)
    {
        return;
    }
    object->addToPath(point, point);

    if(m_yCanvasMode == DrawMode)
    {
        DrawToReal(object);
    } else if(m_yCanvasMode == EraserMode)
    {
        DoErase(point, point, 30);
    }

    m_yLineObjects.remove(id);
    delete object;
    object = nullptr;
}

void CatCanvasItem::SetBackgroundColor(const QColor &color)
{
    m_yBgColor = color;
    m_pRealCancvas->fill(color);
}

void CatCanvasItem::SetMode(CatCanvasItem::CanvasMode mode)
{
    m_yCanvasMode = mode;
}

void CatCanvasItem::Clear()
{
    m_pRealCancvas->fill(m_yBgColor);
    update();
}

QRectF CatCanvasItem::boundingRect() const
{
    return QRectF(0,0,m_ySize.width(),m_ySize.height());
}

void CatCanvasItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->drawImage(0,0, *m_pRealCancvas);
}

void CatCanvasItem::InitProperty()
{
    m_pRealPainter = nullptr;
    m_pRealCancvas = nullptr;
    m_pCatCanvasDoubleBuffering = nullptr;
}

void CatCanvasItem::ReSize(const QSizeF &size)
{
    m_ySize = size;
}

void CatCanvasItem::DrawToReal(CatLineObject *object)
{
    m_pRealPainter->setRenderHint(QPainter::Antialiasing, true);
    m_pRealPainter->setCompositionMode(QPainter::CompositionMode_Source);
    m_pRealPainter->setPen(QPen(Qt::red, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    QPainterPath path = object->StrokePath(5);
    m_pRealPainter->fillPath(path, Qt::red);

    m_pCatCanvasDoubleBuffering->Clear();
    this->update(path.boundingRect());
}

void CatCanvasItem::InitCanvas()
{
    m_pRealCancvas = new QImage(m_ySize.toSize(), QImage::Format_ARGB32_Premultiplied);
    m_pRealCancvas->fill(Qt::transparent);


    m_pRealPainter = new QPainter(m_pRealCancvas);

    m_pCatCanvasDoubleBuffering = new CatCanvasDoubleBuffering(m_ySize, this);
    m_pCatCanvasDoubleBuffering->setZValue(10);
}

void CatCanvasItem::DoErase(QPointF pos1, QPointF pos2, int width)
{
    QPainterPath path = CreateStrokePath(pos1, pos2, width);

    m_pRealPainter->setRenderHint(QPainter::Antialiasing, true);
    m_pRealPainter->setCompositionMode(QPainter::CompositionMode_Source);
    m_pRealPainter->setPen(QPen(Qt::transparent, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    m_pRealPainter->fillPath(path, Qt::transparent);

    update();
}

QPainterPath CatCanvasItem::CreateStrokePath(const QPointF &pos1, const QPointF &pos2, int width)
{
    QPainterPath path;
    path.moveTo(pos1);
    path.lineTo(pos2);

    if(path.isEmpty())
    {
        path.addRegion(QRegion(QRect(pos1.x() - 0.5, pos2.y() - 0.5, 1, 1),
                               QRegion::Ellipse));
    }

    QPainterPathStroker stroker;
    stroker.setWidth(width);
    stroker.setCapStyle(Qt::RoundCap);
    stroker.setJoinStyle(Qt::RoundJoin);

    return stroker.createStroke(path);
}

/*
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
*/