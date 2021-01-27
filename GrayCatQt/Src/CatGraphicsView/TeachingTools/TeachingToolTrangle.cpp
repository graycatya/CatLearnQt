#include "TeachingToolTrangle.h"
#include <QGraphicsSvgItem>
#include <QPainter>
#include <QPainterPath>
#include <QGraphicsSceneHoverEvent>
#include <QCursor>
#include <QGraphicsView>
#include <QDebug>
#include <math.h>

#include "CatMath.h"

const int sLeftEdgeMargin = 10;
const int centimeterGraduationHeight = 15;
const int halfCentimeterGraduationHeight = 10;
const int millimeterGraduationHeight = 5;
const int millimetersPerCentimeter = 10;
const int millimetersPerHalfCentimeter = 5;
//const float inchSize = 25.4f;
const int sRoundingRadius = sLeftEdgeMargin / 2;
const int sBackgauge = 70;
const int sArrowLength = 30;
const int sMinWidth = 240;
const int sMinHeight = 210;
//const int sDefineHeight = 400;

TeachingToolTrangle::TeachingToolTrangle()
{
    InitProperty();
}

TeachingToolTrangle::~TeachingToolTrangle()
{

}

QRectF TeachingToolTrangle::boundingRect() const
{
    return Rect();
}

void TeachingToolTrangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter->setRenderHint(QPainter::TextAntialiasing, true);

    QPolygonF polygon;

    if(mShouldPaintInnerTriangle)
    {
        QPen pen1;
        painter->save();
        pen1.setColor(QColor(0, 0, 0, 0));
        pen1.setWidthF(0);
        QPen pen2;
        pen2.setColor(TrangleBorderColor);
        pen2.setWidthF(1);

        painter->setPen(pen1);
        painter->setBrush(TrangleBackgroundColor);
        polygon << A1 << A2 << B2 << B1;
        painter->drawPolygon(polygon);
        polygon.clear();


        polygon << B1 << B2 << C2 << C1;
        painter->drawPolygon(polygon);
        polygon.clear();

        polygon << C1 << C2 << A2 << A1;
        painter->drawPolygon(polygon);
        polygon.clear();
        painter->restore();

        painter->save();
        painter->setPen(pen2);
        painter->setBrush(Qt::NoBrush);
        polygon << A1 << B1 << C1;
        painter->drawPolygon(polygon);
        polygon.clear();
        polygon << A2 << B2 << C2;
        painter->drawPolygon(polygon);
        painter->restore();

    } else {

        QPen pen2;
        pen2.setColor(TrangleBorderColor);
        pen2.setWidthF(1);
        painter->save();
        painter->setPen(pen2);
        painter->setBrush(TrangleBackgroundColor);
        polygon << A1 << B1 << C1;
        painter->drawPolygon(polygon);
        polygon.clear();
        painter->restore();

    }



    m_pCloseButton->setPos(CloseButtonRect().topLeft());
    m_pFlipHorizontalButton->setPos(FlipHorizontalButtonRect().topLeft());
    m_pFlipVerticalButton->setPos(FlipVerticalButtonRect().topLeft());
    m_pRotateButton->setPos(RotateButtonRect().topLeft());

    paintGraduations(painter);

    // 绘制改变大小按钮
    painter->save();
    painter->setBrush(TrangleResizeButtonColor);

    if(mShowResize1)
    {
        painter->drawPolygon(resize1Polygon());
    }

    if(mShowResize2)
    {
        painter->drawPolygon(resize2Polygon());
    }

    painter->restore();
}

QPainterPath TeachingToolTrangle::shape() const
{
    QPainterPath path;
    QPolygonF polygon;

    polygon << A1 << B1 << C1;
    path.addPolygon(polygon);
    polygon.clear();

    polygon << A2 << B2 << C2;
    path.addPolygon(polygon);
    polygon.clear();

    return path;
}

void TeachingToolTrangle::SetCloseButtonSvg(QString svg)
{
    if(CloseButtonSvg != svg)
    {
        if(m_pCloseButton != nullptr)
        {
            m_pCloseButton->deleteLater();
            m_pCloseButton = nullptr;
        }
        CloseButtonSvg = svg;
        m_pCloseButton = new QGraphicsSvgItem(svg, this);
        prepareGeometryChange();
    }
}

void TeachingToolTrangle::SetRotateButtonSvg(QString svg)
{
    if(RotateButtonSvg != svg)
    {
        if(m_pRotateButton != nullptr)
        {
            m_pRotateButton->deleteLater();
            m_pRotateButton = nullptr;
        }
        RotateButtonSvg = svg;
        m_pRotateButton = new QGraphicsSvgItem(svg, this);
        prepareGeometryChange();
    }
}

void TeachingToolTrangle::SetFlipHorizontalButtonSvg(QString svg)
{
    if(FlipHorizontalButtonSvg != svg)
    {
        if(m_pFlipHorizontalButton != nullptr)
        {
            m_pFlipHorizontalButton->deleteLater();
            m_pFlipHorizontalButton = nullptr;
        }
        FlipHorizontalButtonSvg = svg;
        m_pFlipHorizontalButton = new QGraphicsSvgItem(svg, this);
        prepareGeometryChange();
    }
}

void TeachingToolTrangle::SetFlipVerticalButtonSvg(QString svg)
{
    if(FlipVerticalButtonSvg != svg)
    {
        if(m_pFlipVerticalButton != nullptr)
        {
            m_pFlipVerticalButton->deleteLater();
            m_pFlipVerticalButton = nullptr;
        }
        FlipVerticalButtonSvg = svg;
        m_pFlipVerticalButton = new QGraphicsSvgItem(svg, this);
        prepareGeometryChange();
    }
}

void TeachingToolTrangle::SetTrangleBorderColor(QColor color)
{
    TrangleBorderColor = color;
    prepareGeometryChange();
}

void TeachingToolTrangle::SetTrangleBackgroundColor(QColor color)
{
    TrangleBackgroundColor = color;
    prepareGeometryChange();
}

void TeachingToolTrangle::SetTrangleResizeButtonColor(QColor color)
{
    TrangleResizeButtonColor = color;
    prepareGeometryChange();
}

void TeachingToolTrangle::SetTrangleScaleTextColor(QColor color)
{
    TrangleScaleTextColor = color;
    prepareGeometryChange();
}

void TeachingToolTrangle::SetTrangleScaleColor(QColor color)
{
    TrangleScaleColor = color;
    prepareGeometryChange();
}

void TeachingToolTrangle::Move(QPointF lastpot, QPointF currentpot)
{
    //QPointF pos = event->scenePos();
    QPointF move = currentpot - lastpot;
    TopLeftOriginPos = CatMath::PosMove(TopLeftOriginPos, move);
    TopRightOriginPos = CatMath::PosMove(TopRightOriginPos, move);
    BottomLeftOriginPos = CatMath::PosMove(BottomLeftOriginPos, move);
    BottomRightOriginPos = CatMath::PosMove(BottomRightOriginPos, move);
    this->moveBy(move.rx(), move.ry());
}

void TeachingToolTrangle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    UpdateOriginPos();
    if(event->button() == Qt::LeftButton && GetState() != TEAHINGTOOL_STATE_DORMANCY)
    {
        m_yLastRectF = Rect();
        if(GetState() != TEAHINGTOOL_STATE_PEN)
        {
            QPointF pos = event->pos();
            if(resize1Polygon().containsPoint(pos, Qt::OddEvenFill))
            {
                SetState(TEAHINGTOOL_STATE_RESIZE_ONE);
                m_pCloseButton->setVisible(false);
                m_pRotateButton->setVisible(false);
                m_pFlipVerticalButton->setVisible(false);
                m_pFlipHorizontalButton->setVisible(false);
                mShowResize2 = false;
                SetPressPos(pos);
            } else if(resize2Polygon().containsPoint(pos, Qt::OddEvenFill))
            {
                SetState(TEAHINGTOOL_STATE_RESIZE_TWO);
                m_pCloseButton->setVisible(false);
                m_pRotateButton->setVisible(false);
                m_pFlipVerticalButton->setVisible(false);
                m_pFlipHorizontalButton->setVisible(false);
                mShowResize1 = false;
                SetPressPos(pos);
            } else if(FlipVerticalButtonRect().contains(pos))
            {
                m_pCloseButton->setVisible(false);
                m_pRotateButton->setVisible(false);
                m_pFlipHorizontalButton->setVisible(false);
                mShowResize1 = false;
                mShowResize2 = false;
                SetOrientation(VerticalOrientation(mOrientation));
            } else if(FlipHorizontalButtonRect().contains(pos))
            {
                m_pCloseButton->setVisible(false);
                m_pRotateButton->setVisible(false);
                m_pFlipVerticalButton->setVisible(false);
                mShowResize1 = false;
                mShowResize2 = false;
                SetOrientation(HorizontalOrientation(mOrientation));
            } else if(RotateButtonRect().contains(pos))
            {
                SetState(TEAHINGTOOL_STATE_ROTATE);
                m_pCloseButton->setVisible(false);
                m_pFlipVerticalButton->setVisible(false);
                m_pFlipHorizontalButton->setVisible(false);
                mShowResize1 = false;
                mShowResize2 = false;
                SetPressPos(pos);
            } else if(CloseButtonRect().contains(pos))
            {
                SetState(TEAHINGTOOL_STATE_CLOSE);
                m_pRotateButton->setVisible(false);
                m_pFlipVerticalButton->setVisible(false);
                m_pFlipHorizontalButton->setVisible(false);
                mShowResize1 = false;
                mShowResize2 = false;
            } else if(shape().contains(pos))
            {
                SetState(TEAHINGTOOL_STATE_MOVE);
                SetPressPos(event->scenePos());
            }
        } else {
            emit LineStartPos(UpdatePenPos(event));
        }
    }
}

void TeachingToolTrangle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(GetState() != TEAHINGTOOL_STATE_DORMANCY)
    {
        UpdateOriginPos();
        switch (GetState()) {
            case TEAHINGTOOL_STATE_RESIZE_ONE: {
                UpdateResize1RectF(event->pos());
                break;
            }
            case TEAHINGTOOL_STATE_RESIZE_TWO: {
                UpdateResize2RectF(event->pos());
                break;
            }
            case TEAHINGTOOL_STATE_ROTATE: {
                QLineF currentLine(rotationCenter(), event->pos());
                QLineF lastLine(rotationCenter(), event->lastPos());
                rotateAroundCenter(currentLine.angleTo(lastLine));
                UpdateResizeCursor();
                //qDebug() << "angle: " << (360 - angleInDegrees());
                break;
            }
            case TEAHINGTOOL_STATE_MOVE: {
                QPointF pos = event->scenePos();
                QPointF move = pos - PressPos();
                TopLeftOriginPos = CatMath::PosMove(TopLeftOriginPos, move);
                TopRightOriginPos = CatMath::PosMove(TopRightOriginPos, move);
                BottomLeftOriginPos = CatMath::PosMove(BottomLeftOriginPos, move);
                BottomRightOriginPos = CatMath::PosMove(BottomRightOriginPos, move);
                this->moveBy(move.rx(), move.ry());
                SetPressPos(pos);
                break;
            }
            case TEAHINGTOOL_STATE_PEN: {
                    emit LineUpdatePos(UpdatePenPos(event));
                break;
            }
            default: {
                break;
            }
        }
        prepareGeometryChange();
    }
}

void TeachingToolTrangle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    if(GetState() != TEAHINGTOOL_STATE_DORMANCY)
    {
        if(GetState() != TEAHINGTOOL_STATE_PEN)
        {

            if(GetState() == TEAHINGTOOL_STATE_CLOSE)
            {
                SetState(TEAHINGTOOL_STATE_NONE);
                emit Closeed();
                this->deleteLater();
            }  else {

                if(GetState() == TEAHINGTOOL_STATE_RESIZE_ONE)
                {
                    if (mOrientation == TopLeft || mOrientation == BottomLeft)
                    {
                        RightSide = RightSide + deleteX;
                        //qDebug() << "RightSide: " << RightSide;
                    } else {
                        LeftSide = LeftSide - deleteX;
                        //qDebug() << "LeftSize: " << LeftSide;
                    }
                } else if(GetState() == TEAHINGTOOL_STATE_ROTATE) {
                    switch (mOrientation) {
                        case BottomLeft: {
                            TopLeftOriginPos = CatMath::PointCoordinatesOnACircle(BottomLeftOriginPos,
                                                                                  Rect().height(),
                                                                                  (360 - angleInDegrees()) + 270);
                            TopRightOriginPos = CatMath::PointCoordinatesOnACircle(TopLeftOriginPos,
                                                                                   Rect().width() - 20,
                                                                                   (360 - angleInDegrees()));
                            BottomRightOriginPos = CatMath::PointCoordinatesOnACircle(BottomLeftOriginPos,
                                                                                      Rect().width() - 20,
                                                                                      (360 - angleInDegrees()));
                            break;
                        }
                        case BottomRight: {
                            TopRightOriginPos = CatMath::PointCoordinatesOnACircle(BottomRightOriginPos,
                                                                                   Rect().height(),
                                                                                   (360 - angleInDegrees()) + 270);
                            TopLeftOriginPos = CatMath::PointCoordinatesOnACircle(TopRightOriginPos,
                                                                                  Rect().width() - 20,
                                                                                  (360 - angleInDegrees()) + 180);
                            BottomLeftOriginPos = CatMath::PointCoordinatesOnACircle(BottomRightOriginPos,
                                                                                     Rect().width() - 20,
                                                                                     (360 - angleInDegrees()) + 180);
                            break;
                        }
                        case TopLeft: {
                            BottomLeftOriginPos = CatMath::PointCoordinatesOnACircle(TopLeftOriginPos,
                                                                                     Rect().height(),
                                                                                     (360 - angleInDegrees()) + 90);
                            TopRightOriginPos = CatMath::PointCoordinatesOnACircle(TopLeftOriginPos,
                                                                                   Rect().width() - 20,
                                                                                   (360 - angleInDegrees()));
                            BottomRightOriginPos = CatMath::PointCoordinatesOnACircle(BottomLeftOriginPos,
                                                                                      Rect().width() - 20,
                                                                                      (360 - angleInDegrees()));
                            break;
                        }
                        case TopRight: {
                            BottomRightOriginPos = CatMath::PointCoordinatesOnACircle(TopRightOriginPos,
                                                                                      Rect().height(),
                                                                                      (360 - angleInDegrees()) + 90);
                            TopLeftOriginPos = CatMath::PointCoordinatesOnACircle(TopRightOriginPos,
                                                                                  Rect().width() - 20,
                                                                                  (360 - angleInDegrees()) + 180);
                            BottomLeftOriginPos = CatMath::PointCoordinatesOnACircle(BottomRightOriginPos,
                                                                                     Rect().width() - 20,
                                                                                     (360 - angleInDegrees()) + 180);
                            break;
                        }
                    }
                }


                SetState(TEAHINGTOOL_STATE_NONE);
                m_pCloseButton->setVisible(true);
                m_pFlipHorizontalButton->setVisible(true);
                m_pFlipVerticalButton->setVisible(true);
                m_pRotateButton->setVisible(true);
                mShowResize1 = true;
                mShowResize2 = true;
                prepareGeometryChange();
            }
        } else {
            emit LineEnd();
        }
    }
}

void TeachingToolTrangle::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if(GetState() != TEAHINGTOOL_STATE_DORMANCY)
    {
        if(GetState() != TEAHINGTOOL_STATE_PEN)
        {
            QPointF pos = event->pos();
            if(resize1Polygon().containsPoint(pos.toPoint(), Qt::OddEvenFill))
            {
                SetCursor(resizeCursor1());
            } else if(resize2Polygon().containsPoint(pos.toPoint(), Qt::OddEvenFill))
            {
                SetCursor(resizeCursor2());
            } else if(CloseButtonRect().contains(pos))
            {
                SetCursor(CloseCursor);
            } else if(RotateButtonRect().contains(pos))
            {
                SetCursor(RotateCursor);
            } else if(FlipVerticalButtonRect().contains(pos) || FlipHorizontalButtonRect().contains(pos)) {
                SetCursor(QCursor(Qt::ArrowCursor));
            } else if(shape().contains(pos))
            {
                SetCursor(MoveCursor);
                return;
            }
            prepareGeometryChange();
        } else {
            SetCursor(DrawLineRulerCursor);
        }
    }
}

void TeachingToolTrangle::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)
    if(GetState() != TEAHINGTOOL_STATE_DORMANCY)
    {
        emit HoverEntered();
        if(GetState() != TEAHINGTOOL_STATE_PEN)
        {
            m_pCloseButton->setVisible(true);
            m_pFlipHorizontalButton->setVisible(true);
            m_pFlipVerticalButton->setVisible(true);
            m_pRotateButton->setVisible(true);
            mShowResize1 = true;
            mShowResize2 = true;
            prepareGeometryChange();
        } else {
            SetCursor(DrawLineRulerCursor);
        }
    }
}

void TeachingToolTrangle::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)
    if(GetState() != TEAHINGTOOL_STATE_DORMANCY)
    {
        emit HoverLeaveed();
        if(GetState() != TEAHINGTOOL_STATE_PEN)
        {
            SetState(TEAHINGTOOL_STATE_NONE);
            m_pCloseButton->setVisible(false);
            m_pFlipHorizontalButton->setVisible(false);
            m_pFlipVerticalButton->setVisible(false);
            m_pRotateButton->setVisible(false);
            mShowResize1 = false;
            mShowResize2 = false;
            prepareGeometryChange();
        }
        SetCursor(Qt::ArrowCursor);
    }
}

void TeachingToolTrangle::InitProperty()
{
    RotateCursor = QCursor(QPixmap(":/TeachingTool/png/rotate.png"), 16, 16);
    DrawLineRulerCursor = QCursor(QPixmap(":/TeachingTool/png/drawRulerLine.png"), 5, 16);
    MoveCursor = QCursor(Qt::SizeAllCursor);
    CloseCursor = QCursor(Qt::ArrowCursor);
    setAcceptHoverEvents(true);

    SetCloseButtonSvg(":/TeachingTool/svg/closeTool.svg");
    m_pCloseButton->setVisible(false);
    SetRotateButtonSvg(":/TeachingTool/svg/rotateTool.svg");
    m_pRotateButton->setVisible(false);
    SetFlipVerticalButtonSvg(":/TeachingTool/svg/vflipTool.svg");
    m_pFlipVerticalButton->setVisible(false);
    SetFlipHorizontalButtonSvg(":/TeachingTool/svg/hflipTool.svg");
    m_pFlipHorizontalButton->setVisible(false);

    TrangleBackgroundColor = QColor(0xdd, 0xdd, 0xdd, 204);
    TrangleBorderColor = QColor(118,118,118);
    TrangleResizeButtonColor = QColor(0, 0, 0);
    TrangleScaleTextColor = QColor(0, 0, 0);
    TrangleScaleColor = QColor(0, 0, 0);

    SetRect(QRectF(0, 0, 800, 400));
    LeftSide = 0;
    RightSide = 800;

    TopLeftOriginPos = CatMath::PointCoordinatesOnACircle(this->scenePos(),
                                                          10,
                                                          (360 - angleInDegrees()));
    QPointF BottomLeftPos = CatMath::PointCoordinatesOnACircle(this->scenePos(),
                                                               Rect().height(),
                                                               (360 - angleInDegrees()) + 90);
    BottomLeftOriginPos = CatMath::PointCoordinatesOnACircle(BottomLeftPos,
                                                             10,
                                                             (360 - angleInDegrees()));
    TopRightOriginPos = CatMath::PointCoordinatesOnACircle(TopLeftOriginPos,
                                                           Rect().width() - 20,
                                                           (360 - angleInDegrees()));
    BottomRightOriginPos = CatMath::PointCoordinatesOnACircle(BottomLeftOriginPos,
                                                              Rect().width() - 20,
                                                              (360 - angleInDegrees()));

    SetOrientation(BottomLeft);

    UpdateOriginPos();
    UpdateResizeCursor();
}

void TeachingToolTrangle::UpdateResizeCursor()
{
    QPixmap pix(":/TeachingTool/png/resize.png");
    QTransform itemTransform = sceneTransform();
    QRectF itemRect = boundingRect();

    QPointF topLeft = itemTransform.map(itemRect.topLeft());
    QPointF topRight = itemTransform.map(itemRect.topRight());
    QPointF bottomLeft = itemTransform.map(itemRect.bottomLeft());

    QLineF topLine(topLeft, topRight);
    QLineF leftLine(topLeft, bottomLeft);

    qreal angles = topLine.angle();

    QTransform tr1;
    tr1.rotate(- angles);
    mResizeCursor1  = QCursor(pix.transformed(tr1, Qt::SmoothTransformation), pix.width() / 2,  pix.height() / 2);

    angles = leftLine.angle();
    QTransform tr2;
    tr2.rotate(- angles);
    mResizeCursor2 = QCursor(pix.transformed(tr2, Qt::SmoothTransformation), pix.width() / 2,  pix.height() / 2);
}

void TeachingToolTrangle::SetCursor(QCursor cursor)
{
    if(CurrentView != nullptr)
    {
        QGraphicsView *view = CurrentView(this->scene());
        view->setCursor(cursor);
    } else {
        setCursor(cursor);
    }
}

void TeachingToolTrangle::SetOrientation(TeachingToolTrangle::TRANGLEORIENTATION orientation)
{
    mOrientation = orientation;
    CalculatePoints(Rect());
}

void TeachingToolTrangle::UpdateOriginPos()
{
    switch (mOrientation) {
        case BottomLeft:{
            SetOriginPos(QPointF(Rect().bottomLeft().rx() + 10.0,
                                   Rect().bottomLeft().ry()));
            setTransformOriginPoint(OriginPos());
            break;
        }
        case TopLeft:{
            SetOriginPos(QPointF(Rect().topLeft().rx() + 10.0,
                                   Rect().topLeft().ry()));
            setTransformOriginPoint(OriginPos());
            break;
        }
        case TopRight:{
            SetOriginPos(QPointF(Rect().topRight().rx() - 10.0,
                                   Rect().topRight().ry()));
            setTransformOriginPoint(OriginPos());
            break;
        }
        case BottomRight:{
            SetOriginPos(QPointF(Rect().bottomRight().rx() - 10.0,
                                   Rect().bottomRight().ry()));
            setTransformOriginPoint(OriginPos());
            break;
        }
    }
}

void TeachingToolTrangle::UpdateResize1RectF(QPointF pos)
{
    if (mOrientation == TopLeft || mOrientation == BottomLeft)
    {
        qreal deltaX = pos.rx() - PressPos().rx();
        if (m_yLastRectF.width() + deltaX < sMinWidth)
            deltaX = sMinWidth - m_yLastRectF.width();
        SetRect(QRectF(m_yLastRectF.left(), m_yLastRectF.top(),
            m_yLastRectF.width() + deltaX, m_yLastRectF.height()));
        TopRightOriginPos = CatMath::PointCoordinatesOnACircle(TopLeftOriginPos, Rect().width() - 20.0,
                                                               (360 - angleInDegrees()));
        BottomRightOriginPos = CatMath::PointCoordinatesOnACircle(BottomLeftOriginPos, Rect().width() - 20.0,
                                                                  (360 - angleInDegrees()));
        deleteX = deltaX;
    }
    else
    {
        qreal deltaX = PressPos().rx() - pos.rx();
        if (m_yLastRectF.width() + deltaX < sMinWidth)
            deltaX = sMinWidth - m_yLastRectF.width();
        SetRect(QRectF(m_yLastRectF.left() - deltaX, m_yLastRectF.top(),
            m_yLastRectF.width() + deltaX, m_yLastRectF.height()));
        TopLeftOriginPos = CatMath::PointCoordinatesOnACircle(TopRightOriginPos, Rect().width() - 20,
                                                              (360 - angleInDegrees()) + 180);
        BottomLeftOriginPos = CatMath::PointCoordinatesOnACircle(BottomRightOriginPos, Rect().width() - 20,
                                                                 (360 - angleInDegrees()) + 180);
        deleteX = deltaX;
    }
    CalculatePoints(Rect());
}

void TeachingToolTrangle::UpdateResize2RectF(QPointF pos)
{
    if (mOrientation == BottomRight || mOrientation == BottomLeft)
    {
        qreal deltaY = PressPos().ry() - pos.ry();
        if (m_yLastRectF.height() + deltaY < sMinHeight)
            deltaY = sMinHeight - m_yLastRectF.height();
        SetRect(QRectF(m_yLastRectF.left(), m_yLastRectF.top() - deltaY,
                m_yLastRectF.width(), m_yLastRectF.height() + deltaY));
        TopLeftOriginPos = CatMath::PointCoordinatesOnACircle(BottomLeftOriginPos, Rect().height(),
                                                              (360 - angleInDegrees()) + 270);
        TopRightOriginPos = CatMath::PointCoordinatesOnACircle(BottomRightOriginPos, Rect().height(),
                                                               (360 - angleInDegrees()) + 270);
    }
    else
    {
        qreal deltaY = pos.ry() - PressPos().ry();
        if (m_yLastRectF.height() + deltaY < sMinHeight)
            deltaY = sMinHeight - m_yLastRectF.height();

        SetRect(QRectF(m_yLastRectF.left(), m_yLastRectF.top(),
                m_yLastRectF.width(), m_yLastRectF.height() + deltaY));
        BottomLeftOriginPos = CatMath::PointCoordinatesOnACircle(TopLeftOriginPos, Rect().height(),
                                                                 (360 - angleInDegrees()) + 90);
        BottomRightOriginPos = CatMath::PointCoordinatesOnACircle(TopRightOriginPos, Rect().height(),
                                                                  (360 - angleInDegrees()) + 90);
    }
    CalculatePoints(Rect());
}

void TeachingToolTrangle::CalculatePoints(const QRectF &r)
{
    switch (mOrientation) {
        case BottomLeft:{
            A1 = r.topLeft();
            B1 = r.bottomLeft();
            C1 = r.bottomRight();
            break;
        }
        case TopLeft:{
            A1 = r.bottomLeft();
            B1 = r.topLeft();
            C1 = r.topRight();
            break;
        }
        case TopRight:{
            A1 = r.bottomRight();
            B1 = r.topRight();
            C1 = r.topLeft();
            break;
        }
        case BottomRight:{
            A1 = r.topRight();
            B1 = r.bottomRight();
            C1 = r.bottomLeft();
            break;
        }
    }

    C = sqrt(Rect().width() * Rect().width() +
             Rect().height() * Rect().height());
    qreal L = (C * sBackgauge + Rect().width() * sBackgauge)/ Rect().height();
    qreal K = (C * sBackgauge + Rect().height() * sBackgauge)/ Rect().width();

    switch (mOrientation) {
        case BottomLeft:{
            A2.setX(r.left() + sBackgauge); A2.setY(r.top() + K);
            B2.setX(r.left() + sBackgauge); B2.setY(r.bottom() - sBackgauge);
            C2.setX(r.right() - L); C2.setY(r.bottom() - sBackgauge);
            break;
        }
        case TopLeft:{
            A2.setX(r.left() + sBackgauge); A2.setY(r.bottom() - K);
            B2.setX(r.left() + sBackgauge); B2.setY(r.top() + sBackgauge);
            C2.setX(r.right() - L); C2.setY(r.top() + sBackgauge);
            break;
        }
        case TopRight:{
            A2.setX(r.right() - sBackgauge); A2.setY(r.bottom() - K);
            B2.setX(r.right() - sBackgauge); B2.setY(r.top() + sBackgauge);
            C2.setX(r.left() + L); C2.setY(r.top() + sBackgauge);
            break;
        }
        case BottomRight:{
            A2.setX(r.right() - sBackgauge); A2.setY(r.top() + K);
            B2.setX(r.right() - sBackgauge); B2.setY(r.bottom() - sBackgauge);
            C2.setX(r.left() + L); C2.setY(r.bottom() - sBackgauge);
            break;
        }
    }

    bool paintInnerTriangle = true;
    switch (mOrientation) {
        case BottomLeft: {
            if(B2.x() >= C2.x() || B2.y() <= A2.y()){
                paintInnerTriangle = false;
            }
            break;
        }
        case TopLeft: {
            if(B2.x() >= C2.x() || B2.y() >= A2.y()){
                paintInnerTriangle = false;
            }
            break;
        }
        case TopRight: {
            if(B2.x() <= C2.x() || B2.y() >= A2.y()){
                paintInnerTriangle = false;
            }
            break;
        }
        case BottomRight: {
            if(B2.x() <= C2.x() || B2.y() <= A2.y()){
                paintInnerTriangle = false;
            }
            break;
        }
    }

    mShouldPaintInnerTriangle = paintInnerTriangle;
    prepareGeometryChange();
}

QRectF TeachingToolTrangle::CloseButtonRect() const
{
    switch(mOrientation)
    {
        case BottomLeft:
            return QRectF(B2.x() - m_pCloseButton->boundingRect().width() - 5,
              B2.y() - m_pCloseButton->boundingRect().height() - 5,
              m_pCloseButton->boundingRect().width(),
              m_pCloseButton->boundingRect().height());
        case TopLeft:
            return QRectF(B2.x() - m_pCloseButton->boundingRect().width() - 5,
              B2.y() + 5,
              m_pCloseButton->boundingRect().width(),
              m_pCloseButton->boundingRect().height());
        case TopRight:
            return QRectF(B2.x() + 5,
              B2.y() + 5,
              m_pCloseButton->boundingRect().width(),
              m_pCloseButton->boundingRect().height());
        case BottomRight:
            return QRectF(B2.x() + 5,
              B2.y() - m_pCloseButton->boundingRect().height() - 5,
              m_pCloseButton->boundingRect().width(),
              m_pCloseButton->boundingRect().height());
    }
    return QRectF(0,0,0,0);
}

QRectF TeachingToolTrangle::RotateButtonRect() const
{
    QPointF p(C2);
    qreal buttonsX = FlipVerticalButtonRect().left();

    switch(mOrientation)
    {
        case BottomLeft:
            p = QPointF(qMax(p.x() + 20, buttonsX), p.y() + 5);
            break;
        case TopLeft:
            p = QPointF(qMax(p.x() + 20, buttonsX), p.y() -5 - m_pRotateButton->boundingRect().height());
            break;
        case TopRight:
            p = QPointF(qMin(p.x() -20 - m_pRotateButton->boundingRect().width(), buttonsX), p.y() - 5 - m_pRotateButton->boundingRect().height());
            break;
        case BottomRight:
            p = QPointF(qMin(p.x() -20 - m_pRotateButton->boundingRect().width(), buttonsX), p.y() + 5);
            break;
    }
    return QRectF(p, QSizeF(m_pRotateButton->boundingRect().size()));
}

QRectF TeachingToolTrangle::FlipVerticalButtonRect() const
{
    qreal dy = m_pCloseButton->boundingRect().height() + 5;
    switch(mOrientation)
    {
        case BottomLeft:
            return QRectF(B2.x() - m_pFlipVerticalButton->boundingRect().width() - 5,
              B2.y() - m_pFlipVerticalButton->boundingRect().height() - 5 - dy,
              m_pFlipVerticalButton->boundingRect().width(),
              m_pFlipVerticalButton->boundingRect().height());
        case TopLeft:
            return QRectF(B2.x() - m_pFlipVerticalButton->boundingRect().width() - 5,
              B2.y() + 5 + dy,
              m_pFlipVerticalButton->boundingRect().width(),
              m_pFlipVerticalButton->boundingRect().height());
        case TopRight:
            return QRectF(B2.x() + 5,
              B2.y() + 5 + dy,
              m_pFlipVerticalButton->boundingRect().width(),
              m_pFlipVerticalButton->boundingRect().height());
        case BottomRight:
            return QRectF(B2.x() + 5,
              B2.y() - m_pFlipVerticalButton->boundingRect().height() - 5 - dy,
              m_pFlipVerticalButton->boundingRect().width(),
              m_pFlipVerticalButton->boundingRect().height());
    }
    return QRectF(0,0,0,0);
}

QRectF TeachingToolTrangle::FlipHorizontalButtonRect() const
{
    qreal dy = m_pFlipVerticalButton->boundingRect().height() + m_pCloseButton->boundingRect().height() + 10;
    switch(mOrientation)
    {
        case BottomLeft:
            return QRectF(B2.x() - m_pFlipHorizontalButton->boundingRect().width() - 5,
              B2.y() - m_pFlipHorizontalButton->boundingRect().height() - 5 - dy,
              m_pFlipHorizontalButton->boundingRect().width(),
              m_pFlipHorizontalButton->boundingRect().height());
        case TopLeft:
            return QRectF(B2.x() - m_pFlipHorizontalButton->boundingRect().width() - 5,
              B2.y() + 5 + dy,
              m_pFlipHorizontalButton->boundingRect().width(),
              m_pFlipHorizontalButton->boundingRect().height());
        case TopRight:
            return QRectF(B2.x() + 5,
              B2.y() + 5 + dy,
              m_pFlipHorizontalButton->boundingRect().width(),
              m_pFlipHorizontalButton->boundingRect().height());
        case BottomRight:
            return QRectF(B2.x() + 5,
              B2.y() - m_pFlipHorizontalButton->boundingRect().height() - 5 - dy,
              m_pFlipHorizontalButton->boundingRect().width(),
              m_pFlipHorizontalButton->boundingRect().height());
    }
    return QRectF(0,0,0,0);
}

QPolygonF TeachingToolTrangle::resize1Polygon() const
{
    qreal x1, y1;
    switch (mOrientation)
    {
        case BottomLeft:{
            x1 = -1;
            y1 = -1;
            break;
        }
        case TopLeft:{
            x1 = -1;
            y1 = 1;
            break;
        }
        case TopRight:{
            x1 = 1;
            y1 = 1;
            break;
        }
        case BottomRight:{
            x1 = 1;
            y1 = -1;
            break;
        }
    }
    QPointF P1(C1.x() + x1 * sArrowLength, C1.y());
    QPointF P2(C1.x() + x1 * sArrowLength * boundingRect().width()/C,
               C1.y() + y1 * sArrowLength * boundingRect().height()/C);
    QPolygonF p;
    p << C1 << P1 << P2;
    return p;
}

QPolygonF TeachingToolTrangle::resize2Polygon() const
{
    qreal x1, y1;
    switch (mOrientation) {
        case BottomLeft:{
            x1 = 1;
            y1 = 1;
            break;
        }
        case TopLeft:{
            x1 = 1;
            y1 = -1;
            break;
        }
        case TopRight:{
            x1 = -1;
            y1 = -1;
            break;
        }
        case BottomRight:{
            x1 = -1;
            y1 = 1;
            break;
        }
    }
    QPointF P1(A1.x(), A1.y() + y1 * sArrowLength);
    QPointF P2(A1.x() + x1 * sArrowLength * boundingRect().width() / C,
               A1.y() + y1 * sArrowLength * boundingRect().height() / C);
    QPolygonF p;
    p << A1 << P1 << P2;
    return p;
}

QCursor TeachingToolTrangle::resizeCursor1() const
{
    return mResizeCursor1;
}

QCursor TeachingToolTrangle::resizeCursor2() const
{
    return mResizeCursor2;
}

TeachingToolTrangle::TRANGLEORIENTATION TeachingToolTrangle::VerticalOrientation(TeachingToolTrangle::TRANGLEORIENTATION Orientation)
{
    TeachingToolTrangle::TRANGLEORIENTATION temp = Orientation;
    if(Orientation == BottomLeft)
    {
        temp = TopLeft;
    } else if(Orientation == TopLeft)
    {
        temp = BottomLeft;
    } else if(Orientation == BottomRight)
    {
        temp = TopRight;
    } else if(Orientation == TopRight)
    {
        temp = BottomRight;
    }
    return temp;
}

TeachingToolTrangle::TRANGLEORIENTATION TeachingToolTrangle::HorizontalOrientation(TeachingToolTrangle::TRANGLEORIENTATION Orientation)
{
    TeachingToolTrangle::TRANGLEORIENTATION temp = Orientation;
    if(Orientation == BottomLeft)
    {
        temp = BottomRight;
    } else if(Orientation == BottomRight)
    {
        temp = BottomLeft;
    } else if(Orientation == TopRight)
    {
        temp = TopLeft;
    } else if(Orientation == TopLeft)
    {
        temp = TopRight;
    }
    return temp;
}

QPointF TeachingToolTrangle::rotationCenter() const
{
    switch(mOrientation)
    {
        case BottomLeft:
        case TopLeft:
            return B1 + QPointF(sLeftEdgeMargin, 0);
        case TopRight:
        case BottomRight:
            return B1 - QPointF(sLeftEdgeMargin, 0);
    }
    return QPointF(0, 0);
}

void TeachingToolTrangle::rotateAroundCenter(qreal angles)
{
    qreal oldAngle = this->angle;
    this->angle = angles;
    QTransform transform;
    rotateAroundCenter(transform, rotationCenter());
    setTransform(transform, true);
    this->angle = oldAngle + angles;
}

void TeachingToolTrangle::rotateAroundCenter(QTransform &transform, QPointF center)
{
    transform.translate(center.x(), center.y());
    transform.rotate(angle);
    transform.translate(- center.x(), - center.y());
}

void TeachingToolTrangle::paintGraduations(QPainter *painter)
{
    const int SEPARATOR = 5;
    qreal kx = (mOrientation == TopLeft || mOrientation == BottomLeft) ? 1 : -1;
    qreal ky = (mOrientation == BottomLeft || mOrientation == BottomRight) ? 1 : -1;
    painter->save();
    QFontMetricsF fontMetrics(painter->font());
    sPixelsPerCentimeter = CatMath::CmtoPx(1);
    double pixelsPerMillimeter = sPixelsPerCentimeter/10.0;
    double numbersWidth = fontMetrics.width("00");
        bool shouldDisplayAllNumbers = (numbersWidth <= (sPixelsPerCentimeter - 5));

        for (int millimeters = 0; millimeters < (Rect().width() - sLeftEdgeMargin - sRoundingRadius) / pixelsPerMillimeter; millimeters++)
        {
            double graduationX = rotationCenter().x() + kx * pixelsPerMillimeter * millimeters;
            double graduationHeight = 0;

            if (millimeters % millimetersPerCentimeter == 0)
                graduationHeight = centimeterGraduationHeight;

            else if (millimeters % millimetersPerHalfCentimeter == 0)
                graduationHeight = halfCentimeterGraduationHeight;

            else
                graduationHeight = millimeterGraduationHeight;

            qreal requiredSpace = graduationHeight + SEPARATOR ;
            /*     B____C
                    |  /
                   D|_/E <-- availableSpace Thalès
                    |/
                    A
            */

            qreal AD;
            switch(mOrientation)
            {
                case BottomLeft:
                    AD = QLineF(Rect().bottomRight(), QPointF(graduationX, rotationCenter().y())).length();
                    break;
                case TopLeft:
                    AD = QLineF(Rect().topRight(), QPointF(graduationX, rotationCenter().y())).length();
                    break;
                case TopRight:
                    AD = QLineF(Rect().topLeft(), QPointF(graduationX, rotationCenter().y())).length();
                    break;
                case BottomRight:
                    AD = QLineF(Rect().bottomLeft(), QPointF(graduationX , rotationCenter().y())).length();
                    break;
            }

            qreal AB = Rect().width();
            qreal BC = Rect().height();
            qreal DE =  AD * BC / AB, availableSpace = DE;

            if (availableSpace < requiredSpace)
                break;

            if (shouldDisplayAllNumbers || millimeters % millimetersPerHalfCentimeter == 0)
            {
                QPen pen = painter->pen();
                pen.setColor(TrangleScaleColor);
                painter->setPen(pen);
                painter->setBrush(TrangleScaleColor);
                painter->drawLine(QLineF(graduationX, rotationCenter().y(),
                                         graduationX, rotationCenter().y()
                                         - ky * graduationHeight));
            }
            if ((shouldDisplayAllNumbers && millimeters % millimetersPerCentimeter == 0)
                || millimeters % (millimetersPerCentimeter*5) == 0)
            {
                QString text = QString("%1").arg(static_cast<int>(millimeters / millimetersPerCentimeter));
                qreal textWidth = fontMetrics.width(text);
                qreal textHeight = fontMetrics.tightBoundingRect(text).height();

                requiredSpace = graduationHeight + textHeight + textWidth + SEPARATOR ;

                if (requiredSpace <= availableSpace)
                {
                    int textY = (ky > 0) ? static_cast<int>(rotationCenter().y()
                                                            - static_cast<qreal>(SEPARATOR)
                                                            - centimeterGraduationHeight
                                                            - textHeight)
                        : static_cast<int>(rotationCenter().y() + SEPARATOR + centimeterGraduationHeight);
                    QPen pen = painter->pen();
                    pen.setColor(TrangleScaleTextColor);
                    painter->setPen(pen);
                    painter->setBrush(TrangleScaleTextColor);
                    painter->drawText(QRectF(graduationX - textWidth / 2,
                                             textY, textWidth, textHeight),
                                      Qt::AlignVCenter, text);
                }
            }
        }
        painter->restore();
}

qreal TeachingToolTrangle::angleInDegrees() const
{
    QRectF itemRect = boundingRect();
    QTransform itemTransform = sceneTransform();
    QPointF topLeft = itemTransform.map(itemRect.topLeft());
    QPointF topRight = itemTransform.map(itemRect.topRight());
    QLineF topLine(topLeft, topRight);
    return topLine.angle();
}

QPointF TeachingToolTrangle::UpdatePenPos(QGraphicsSceneMouseEvent *event)
{
    QPointF pos = event->pos();
    //QPointF scenepos = event->scenePos();
    QPointF sceneCurentpos;
    QPointF scentMinPos;
    QPointF scentMaxPos;
    QPointF UpdatePos;
    switch(mOrientation)
    {
        case BottomLeft:
        case BottomRight:
        {
            scentMinPos = CatMath::PointCoordinatesOnACircle(BottomLeftOriginPos, PenWidth()/2, (360 - angleInDegrees()) + 90);
            scentMaxPos = CatMath::PointCoordinatesOnACircle(BottomRightOriginPos, PenWidth()/2, (360 - angleInDegrees()) + 90);
            sceneCurentpos = scentMinPos;
            break;
        }
        case TopLeft:
        case TopRight:
        {
            scentMinPos = CatMath::PointCoordinatesOnACircle(TopLeftOriginPos, PenWidth()/2, (360 - angleInDegrees()) + 270);
            scentMaxPos = CatMath::PointCoordinatesOnACircle(TopRightOriginPos, PenWidth()/2, (360 - angleInDegrees()) + 270);
            sceneCurentpos = scentMinPos;
            break;
        }
    }
    if(pos.rx() < LeftSide + 10)
    {
        UpdatePos = scentMinPos;
    } else if(pos.rx() > RightSide - 10)
    {
        UpdatePos = scentMaxPos ;
    } else {
        QLineF line = QLineF(QPointF(LeftSide, 0), QPointF(pos.rx(), 0));
        QPointF scentMousePos = CatMath::PointCoordinatesOnACircle(sceneCurentpos,
                                                                   line.length(), (360 - angleInDegrees()));
       UpdatePos = scentMousePos;
    }
    return UpdatePos;
}
