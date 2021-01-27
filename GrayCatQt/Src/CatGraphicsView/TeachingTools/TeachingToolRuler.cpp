#include "TeachingToolRuler.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSvgItem>
#include <QPainter>
#include <QGraphicsSceneHoverEvent>
#include <QCursor>
#include <QDebug>

#include "CatMath.h"

TeachingToolRuler::TeachingToolRuler()
{
    InitProperty();
}

TeachingToolRuler::~TeachingToolRuler()
{

}

QRectF TeachingToolRuler::boundingRect() const
{
    return Rect();
}

void TeachingToolRuler::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter->setRenderHint(QPainter::TextAntialiasing, true);
    painter->save();
    // [0] 绘制直尺本体
    PaintBody(painter);
    // [1] 按钮绘制
    PaintButton();
    // [3] 刻度绘制
    PaintScale(painter);
    // [4] 旋转状态绘制
    if(GetState() == TEAHINGTOOL_STATE_ROTATE)
    {
        PaintRotate(painter);
    }

    painter->restore();
}

QPainterPath TeachingToolRuler::shape() const
{
    QPainterPath path;
    path.addRoundedRect(Rect(), RulerBorderRadius, RulerBorderRadius);
    return path;
}

void TeachingToolRuler::SetRulerBorderRadius(int radius)
{
    RulerBorderRadius = radius;
}

void TeachingToolRuler::SetRulerBackgroundColor(QColor color)
{
    RulerBackgroundColor = color;
}

void TeachingToolRuler::SetRulerBorderColor(QColor color)
{
    RulerBorderColor = color;
}

void TeachingToolRuler::SetRulerScaleTextColor(QColor color)
{
    RulerScaleTextColor = color;
}

void TeachingToolRuler::SetRulerScaleColor(QColor color)
{
    RulerScaleColor = color;
}

void TeachingToolRuler::SetRulerRotateColor(QColor color)
{
    RulerRotateColor = color;
}

void TeachingToolRuler::SetCloseButtonSvg(QString svg)
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

void TeachingToolRuler::SetResizeButtonSvg(QString svg)
{
    if(ResizeButtonSvg != svg)
    {
        if(m_pResizeButton != nullptr)
        {
            m_pResizeButton->deleteLater();
            m_pResizeButton = nullptr;
        }
        ResizeButtonSvg = svg;
        m_pResizeButton = new QGraphicsSvgItem(svg, this);
        prepareGeometryChange();
    }
}

void TeachingToolRuler::SetRotateButtonSvg(QString svg)
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

void TeachingToolRuler::InitProperty()
{
    RotateCursor = QCursor(QPixmap(":/TeachingTool/png/rotate.png"), 16, 16);
    DrawLineRulerCursor = QCursor(QPixmap(":/TeachingTool/png/drawRulerLine.png"), 5, 16);
    ResizeCursor = QCursor(QPixmap(":/TeachingTool/png/resize.png"), 16, 16);
    MoveCursor = QCursor(Qt::SizeAllCursor);
    CloseCursor = QCursor(Qt::ArrowCursor);

    SetRect(QRectF(0, 0, CatMath::CmtoPx(21), 96));
    SetMinRect(QRectF(0, 0, CatMath::CmtoPx(5), 96));
    SetMaxRect(QRectF(0, 0, CatMath::CmtoPx(1010), 96));

    SetRulerBorderRadius(6);
    SetRulerBackgroundColor(QColor(255, 255, 255, 204));
    SetRulerBorderColor(QColor(102, 102, 102));
    SetRulerScaleTextColor(RulerBorderColor);
    SetRulerScaleColor(RulerScaleTextColor);
    SetRulerRotateColor(RulerScaleColor);
    //qDebug() << CurrentPath();

    setAcceptHoverEvents(true);

    SetResizeButtonSvg(":/TeachingTool/svg/resizeRuler.svg");
    m_pResizeButton->setVisible(false);
    SetCloseButtonSvg(":/TeachingTool/svg/closeTool.svg");
    m_pCloseButton->setVisible(false);
    SetRotateButtonSvg(":/TeachingTool/svg/rotateTool.svg");
    m_pRotateButton->setVisible(false);

    SetOriginPos(QPointF(10,0));
    setTransformOriginPoint(OriginPos());
    UpdateResizeCursor();
}

void TeachingToolRuler::UpdateResizeCursor()
{
    QPixmap pix(":/TeachingTool/png/resize.png");
    QTransform tr;
    tr.rotate(this->rotation());
    ResizeCursor  = QCursor(pix.transformed(tr, Qt::SmoothTransformation), pix.width() / 2,  pix.height() / 2);
}

void TeachingToolRuler::SetCursor(QCursor cursor)
{
    if(CurrentView != nullptr)
    {
        QGraphicsView *view = CurrentView(this->scene());
        view->setCursor(cursor);
    } else {
        setCursor(cursor);
    }

}

QRectF TeachingToolRuler::CloseButtonRect() const
{
    QPixmap pixmap(CloseButtonSvg);
    QSizeF size(pixmap.rect().width(),
                pixmap.rect().height());
    QPointF topleft(size.width()/2,
                    (Rect().height() - size.height())/2);
    return QRectF(topleft, size);
}

QRectF TeachingToolRuler::ResizeButtonRect() const
{
    QPixmap pixmap(ResizeButtonSvg);
    QSizeF size(pixmap.rect().width(),
                pixmap.rect().height());
    QPointF topleft(Rect().width() - size.width(),
                    0);
    return QRectF(topleft, size);
}

QRectF TeachingToolRuler::RotateButtonRect() const
{
    QPixmap pixmap(RotateButtonSvg);
    QSizeF size(pixmap.rect().width(),
                pixmap.rect().height());
    QPointF topleft(ResizeButtonRect().x() - size.width() - size.width()/2,
                    (Rect().height() - size.height())/2);
    return QRectF(topleft, size);
}

void TeachingToolRuler::PaintBody(QPainter *painter)
{
    QPen pen = painter->pen();
    pen.setColor(RulerBorderColor);
    painter->setPen(pen);
    painter->setBrush(QBrush(RulerBackgroundColor));
    painter->drawRoundedRect(QRectF(QPointF(0,0), Rect().size()), RulerBorderRadius, RulerBorderRadius);
}

void TeachingToolRuler::PaintButton()
{
    // [1] resize按钮
    m_pResizeButton->setPos(ResizeButtonRect().x(), ResizeButtonRect().y());

    // [2] close按钮
    m_pCloseButton->setPos(CloseButtonRect().x(), CloseButtonRect().y());

    // [3] rotate按钮
    m_pRotateButton->setPos(RotateButtonRect().x(), RotateButtonRect().y());
}

void TeachingToolRuler::PaintScale(QPainter *painter)
{
    QFont font = painter->font();
    font.setPixelSize(14);
    QPen pen = painter->pen();
    pen.setColor(RulerScaleColor);
    painter->setPen(pen);
    painter->setFont(font);
    int scalevalue = 0;
    int value = 0;
    qreal scalelocation = 10;
    qreal longscaleheight = CatMath::CmtoPx(1)/2;
    qreal scaleheight = longscaleheight*(2.0/3.0);
    qreal shortscaleheight = scaleheight/2;

    QFontMetrics fm(font);
    while(scalelocation < Rect().width() - 10)
    {
        if(scalevalue == 0)
        {
            int pixelsWide = fm.horizontalAdvance(QString::number(value));
            painter->drawLine(QLineF(scalelocation, 0, scalelocation, longscaleheight));

            // 绘制刻度文字
            painter->drawText(QPointF(scalelocation - pixelsWide/2 , longscaleheight + 14 + 1),
                              QString::number(value));

            painter->drawLine(QLineF(scalelocation, Rect().height(),
                                     scalelocation, Rect().height() - longscaleheight));

            // 绘制刻度文字
            painter->drawText(QPointF(scalelocation - pixelsWide/2 ,
                                      Rect().height() - longscaleheight - 5),
                              QString::number(value));

        } else if(scalevalue == 5)
        {
            painter->drawLine(QLineF(scalelocation, 0, scalelocation, scaleheight));

            painter->drawLine(QLineF(scalelocation, Rect().height(), scalelocation,
                                     Rect().height() - scaleheight));
        } else {
            painter->drawLine(QLineF(scalelocation, 0, scalelocation, shortscaleheight));

            painter->drawLine(QLineF(scalelocation, Rect().height(), scalelocation,
                                     Rect().height() - shortscaleheight));
        }

        scalevalue += 1;
        if(scalevalue == 10)
        {
            value++;
            scalevalue = 0;
        }

        scalelocation += CatMath::CmtoPx(0.1);
    }
}

void TeachingToolRuler::PaintRotate(QPainter *painter)
{
    QPen pen = painter->pen();
    pen.setColor(RulerRotateColor);
    painter->setPen(pen);
    qreal longscaleheight = CatMath::CmtoPx(1);
    painter->drawArc(QRectF(-(longscaleheight/2) + 10, -(longscaleheight/2), longscaleheight, longscaleheight), 0 * 16, -90 * 16);
}

void TeachingToolRuler::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    if(event->button() == Qt::LeftButton && GetState() != TEAHINGTOOL_STATE_DORMANCY)
    {
        if(GetState() != TEAHINGTOOL_STATE_PEN)
        {
            if(ResizeButtonRect().contains(event->pos()))
            {
                SetState(TEAHINGTOOL_STATE_RESIZE_ONE);
                m_pRotateButton->setVisible(false);
                m_pCloseButton->setVisible(false);
                SetPressPos(event->pos());
            } else if(RotateButtonRect().contains(event->pos()))
            {
                SetState(TEAHINGTOOL_STATE_ROTATE);
                m_pResizeButton->setVisible(false);
                m_pCloseButton->setVisible(false);
                SetPressPos(event->pos());
            } else if(CloseButtonRect().contains(event->pos()))
            {
                SetState(TEAHINGTOOL_STATE_CLOSE);
                m_pResizeButton->setVisible(false);
                m_pRotateButton->setVisible(false);
            } else if(boundingRect().contains(event->pos()))
            {
                SetState(TEAHINGTOOL_STATE_MOVE);
                m_pCloseButton->setVisible(false);
                m_pResizeButton->setVisible(false);
                m_pRotateButton->setVisible(false);
                SetPressPos(event->scenePos());
            }
        } else {
            // 先获取scentPos
            QPointF pos = event->pos();
            QPointF sceneTopPenPos = CatMath::PointCoordinatesOnACircle(this->scenePos(), PenWidth()/2, this->rotation() + 270);
            QPointF sceneBottompos = CatMath::PointCoordinatesOnACircle(this->scenePos(), Rect().height() + PenWidth()/2, this->rotation() + 90);
            QPointF scentTopMinPos = CatMath::PointCoordinatesOnACircle(sceneTopPenPos, OriginPos().x(), this->rotation());
            QPointF scentTopMaxPos = CatMath::PointCoordinatesOnACircle(sceneTopPenPos, Rect().width() - 10, this->rotation());
            QPointF scentBottomMinPos = CatMath::PointCoordinatesOnACircle(sceneBottompos, OriginPos().x(), this->rotation());
            QPointF scentBottomMaxPos = CatMath::PointCoordinatesOnACircle(sceneBottompos, Rect().width() - 10, this->rotation());

            QPointF StartPos;
            if(pos.ry() > Rect().height()/2.0)
            {
                DrawLineState = BOTTOM;
            } else {
                DrawLineState = TOP;
            }

            switch (DrawLineState) {
                case BOTTOM:{
                    //qDebug() << "BOTTOM";
                    if(pos.rx() < 10.0)
                    {
                        StartPos = scentBottomMinPos;
                    } else if(pos.rx() > Rect().width() - 10.0)
                    {
                        StartPos = scentBottomMaxPos;
                    } else {
                        QPointF scentMousePos = CatMath::PointCoordinatesOnACircle(sceneBottompos,
                                                                                   pos.x(), this->rotation());
                        StartPos = scentMousePos;
                    }
                    break;
                }
                case TOP:{
                    //qDebug() << "TOP";
                    if(pos.rx() < 10.0)
                    {
                        StartPos = scentTopMinPos;
                    } else if(pos.rx() > Rect().width() - 10.0)
                    {
                        StartPos = scentTopMaxPos;
                    } else {
                        QPointF scentMousePos = CatMath::PointCoordinatesOnACircle(sceneTopPenPos,
                                                                                   pos.x(), this->rotation());
                        StartPos = scentMousePos;
                    }
                    break;
                }
            }
            emit LineStartPos(StartPos);
        }
    }
}

void TeachingToolRuler::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(GetState() != TEAHINGTOOL_STATE_DORMANCY)
    {
        switch(GetState())
        {
            case TEAHINGTOOL_STATE_MOVE:{
                QPointF pos = event->scenePos();
                QPointF move = pos - PressPos();
                this->moveBy(move.rx(), move.ry());
                SetPressPos(pos);
                break;
            }
            case TEAHINGTOOL_STATE_RESIZE_ONE:{
                QPointF pos = event->pos();
                QPointF size = pos - PressPos();
                qreal width = Rect().width() + size.rx();
                if(width < MinRect().width())
                {
                     SetRect(MinRect());
                } else if(width >MaxRect().width())
                {
                    SetRect(MaxRect());
                } else {
                    SetRect(QRectF(Rect().x(), Rect().y(), width, Rect().height()));
                }
                SetPressPos(pos);
                break;
            }
            case TEAHINGTOOL_STATE_ROTATE:{
                QPointF pos = event->pos();
                QVector2D Start = QVector2D(PressPos() - QPointF(10.0, 0.0));
                QVector2D End = QVector2D(pos - QPointF(10.0, 0.0));

                qreal angle = 0.0;
                qreal angleEnd = CatMath::DegreeAngle(End);
                qreal angleStart = CatMath::DegreeAngle(Start);
                angle = angleEnd - angleStart + rotation();

                angle = CatMath::AngleJudge(angle);

                setRotation(angle);
                UpdateResizeCursor();
                break;
            }
            case TEAHINGTOOL_STATE_PEN:{
                QPointF pos = event->pos();
                QPointF sceneTopPenPos = CatMath::PointCoordinatesOnACircle(this->scenePos(), PenWidth()/2, this->rotation() + 270);
                QPointF sceneBottompos = CatMath::PointCoordinatesOnACircle(this->scenePos(), Rect().height() + PenWidth()/2, this->rotation() + 90);
                QPointF scentTopMinPos = CatMath::PointCoordinatesOnACircle(sceneTopPenPos, OriginPos().x(), this->rotation());
                QPointF scentTopMaxPos = CatMath::PointCoordinatesOnACircle(sceneTopPenPos, Rect().width() - 10, this->rotation());
                QPointF scentBottomMinPos = CatMath::PointCoordinatesOnACircle(sceneBottompos, OriginPos().x(), this->rotation());
                QPointF scentBottomMaxPos = CatMath::PointCoordinatesOnACircle(sceneBottompos, Rect().width() - 10, this->rotation());

                QPointF UpdatePos;

                switch (DrawLineState) {
                    case BOTTOM:{
                        if(pos.rx() < 10.0)
                        {
                            UpdatePos = scentBottomMinPos;
                        } else if(pos.rx() > Rect().width() - 10.0)
                        {
                            UpdatePos = scentBottomMaxPos;
                        } else {
                            QPointF scentMousePos = CatMath::PointCoordinatesOnACircle(sceneBottompos,
                                                                                       pos.x(), this->rotation());
                            UpdatePos = scentMousePos;
                        }
                        break;
                    }
                    case TOP:{
                        if(pos.rx() < 10.0)
                        {
                            UpdatePos = scentTopMinPos;
                        } else if(pos.rx() > Rect().width() - 10.0)
                        {
                            UpdatePos = scentTopMaxPos;
                        } else {
                            QPointF scentMousePos = CatMath::PointCoordinatesOnACircle(sceneTopPenPos,
                                                                                       pos.x(), this->rotation());
                            UpdatePos = scentMousePos;
                        }
                        break;
                    }

                }
                emit LineUpdatePos(UpdatePos);

                break;
            }
            default: {
                break;
            }
        }

        prepareGeometryChange();
    }
}

void TeachingToolRuler::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
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
            } else {
                SetState(TEAHINGTOOL_STATE_NONE);
                m_pResizeButton->setVisible(true);
                m_pCloseButton->setVisible(true);
                m_pRotateButton->setVisible(true);
                prepareGeometryChange();
            }
        } else {
            emit LineEnd();
        }
    }
}

void TeachingToolRuler::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)
    if(GetState() != TEAHINGTOOL_STATE_DORMANCY)
    {
        if(GetState() != TEAHINGTOOL_STATE_PEN)
        {
            if(ResizeButtonRect().contains(event->pos()))
            {
                SetCursor(ResizeCursor);
            } else if(RotateButtonRect().contains(event->pos()))
            {
                SetCursor(RotateCursor);
            } else if(CloseButtonRect().contains(event->pos()))
            {
                SetCursor(CloseCursor);
            } else {
                SetCursor(MoveCursor);
            }
        } else {
            SetCursor(DrawLineRulerCursor);
        }
    }
}

void TeachingToolRuler::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)
    if(GetState() != TEAHINGTOOL_STATE_DORMANCY)
    {
        emit HoverEntered();
        if(GetState() != TEAHINGTOOL_STATE_PEN)
        {
            SetCursor(MoveCursor);
            m_pResizeButton->setVisible(true);
            m_pCloseButton->setVisible(true);
            m_pRotateButton->setVisible(true);
        } else {
            SetCursor(DrawLineRulerCursor);
        }
    }
}

void TeachingToolRuler::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)

    if(GetState() != TEAHINGTOOL_STATE_DORMANCY)
    {
        emit HoverLeaveed();
        if(GetState() != TEAHINGTOOL_STATE_PEN)
        {
            SetState(TEAHINGTOOL_STATE_NONE);
            m_pResizeButton->setVisible(false);
            m_pCloseButton->setVisible(false);
            m_pRotateButton->setVisible(false);
        }
        SetCursor(Qt::ArrowCursor);
    }
}
