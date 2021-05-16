#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#include "TeachingToolCompass.h"
#include <QGraphicsSvgItem>
#include <QPainter>
#include <QPainterPath>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsView>
#include <QCursor>
#include "CatMath.h"
#include <QDebug>

const qreal CompassesBorderWidth = 1;
const qreal CompassesHeight = 40;
const qreal CompassesSharpWidth = 24;
const qreal CompassesSharpHeight = 2;
const qreal CompassesSharpRectangleWidth = 42;
const qreal CompassesSharpRectangleHeight = 12;
const qreal CompassesSpindleWidth = CompassesHeight;
const qreal CompassesSpindleHeight = CompassesHeight;
const qreal CompassesPenPointRectangleWidth = 42;
const qreal CompassesPenPointRectangleHeight = 12;
const qreal CompassesPenPointWidth = 24;
const qreal CompassesPenPointHeight = 4;
const qreal CompassesOutriggerHeight = 16;


TeachingToolCompass::TeachingToolCompass()
{
    InitProperty();
    this->update();
}

TeachingToolCompass::~TeachingToolCompass()
{

}

QRectF TeachingToolCompass::boundingRect() const
{
    return Rect();
}

void TeachingToolCompass::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter->setRenderHint(QPainter::TextAntialiasing, true);
    // 绘制 圆规尖
    PaintCompassesSharp(painter);
    // 绘制 圆规尖Rectangle
    PaintCompassesSharpRectangle(painter);
    // 绘制 笔尖
    PaintCompassesPenPoint(painter);
    // 绘制 笔尖Rectangle
    PaintCompassesPenPointRectangle(painter);
    // 绘制 支腿
    PaintCompassesOutrigger(painter);
    // 绘制 转轴
    PaintCompassesSpindle(painter);

    if(Rect().width() >= CatMath::CmtoPx(7.6) &&
            (GetState() == TEAHINGTOOL_STATE_ROTATE ||
             GetState() == TEAHINGTOOL_STATE_PEN ||
             GetState() == TEAHINGTOOL_STATE_RESIZE_ONE))
    {
        PaintCompassesLine(painter);
    }

    PaintButton();

}

QPainterPath TeachingToolCompass::shape() const
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addPath(CompassesSharpPath());
    path.addPath(CompassesPenPointPath());
    path.addPath(CompassesOutriggerPath());
    path.addPath(CompassesSpindleRectanglePath());
    path.addPath(CompassesSharpRectanglePath());
    path.addPath(CompassesPenPointRectanglePath());
    return path;
}

void TeachingToolCompass::SetCloseButtonSvg(QString svg)
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

void TeachingToolCompass::SetResizeButtonSvg(QString svg)
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

void TeachingToolCompass::SetCompassesSharpColor(QColor color)
{
    CompassesSharpColor = color;
    prepareGeometryChange();
}

void TeachingToolCompass::SetCompassesSharpRectangleColor(QColor color)
{
    CompassesSharpRectangleColor = color;
    prepareGeometryChange();
}

void TeachingToolCompass::SetCompassesPenPointColor(QColor color)
{
    CompassesPenPointColor = color;
    prepareGeometryChange();
}

void TeachingToolCompass::SetCompassesPenPointRectangleColor(QColor color)
{
    CompassesPenPointRectangleColor = color;
    prepareGeometryChange();
}

void TeachingToolCompass::SetCompassesSpindleRectangleColor(QColor color)
{
    CompassesSpindleRectangleColor = color;
    prepareGeometryChange();
}

void TeachingToolCompass::SetCompassesSpindleRoundnessColor(QColor color)
{
    CompassesSpindleRoundnessColor = color;
    prepareGeometryChange();
}

void TeachingToolCompass::SetCompassesOutriggerColor(QColor color)
{
    CompassesOutriggerColor = color;
    prepareGeometryChange();
}

void TeachingToolCompass::SetCompassesTextColor(QColor color)
{
    CompassesTextColor = color;
    prepareGeometryChange();
}

void TeachingToolCompass::SetCompassesBorderColor(QColor color)
{
    CompassesBorderColor = color;
    prepareGeometryChange();
}

void TeachingToolCompass::InitProperty()
{
    RotateCursor = QCursor(QPixmap(":/TeachingTool/png/rotate.png"), 16, 16);
    PenCircleCursor = QCursor(QPixmap(":/TeachingTool/png/drawCompass.png"), 16, 16);
    ResizeCursor = QCursor(QPixmap(":/TeachingTool/png/resize.png"), 16, 16);
    MoveCursor = QCursor(Qt::SizeAllCursor);
    CloseCursor = QCursor(Qt::ArrowCursor);

    setAcceptHoverEvents(true);
    m_pCloseButton = nullptr;
    m_pResizeButton = nullptr;

    SetRect(QRectF(0, 0, CatMath::CmtoPx(9.4), 40));
    SetMinRect(QRectF(0, 0, CatMath::CmtoPx(6), 40));
    SetMaxRect(QRectF(0, 0, CatMath::CmtoPx(1010), 40));

    CurrentAngle = 0;
    CompassesSpindleBorderRadius = 3;
    CompassesOutriggerBorderRadius = 3;
    CompassesSharpRectangleBorderRadius = 3;
    CompassesPenPointRectangleBorderRadius = 3;
    CompassesOutriggerColor = QColor(215, 215, 215, 204);
    CompassesBorderColor = QColor(130, 130, 130);
    CompassesTextColor = QColor("1d1d1d");
    CompassesSharpColor = QColor(117, 121, 121);
    CompassesSharpRectangleColor = QColor(215, 215, 215, 204);
    CompassesPenPointColor = QColor(27, 27, 27, 204);
    CompassesPenPointRectangleColor = QColor(215, 215, 215, 204);
    CompassesSpindleRectangleColor = QColor(195, 195, 195);
    CompassesSpindleRoundnessColor = QColor(215, 215, 215, 204);

    CompassesSharpRect = QRectF(0, (Rect().height() - CompassesSharpHeight)/2,
                                CompassesSharpWidth, CompassesSharpHeight);
    CompassesSharpRectangleRect = QRectF(CompassesSharpRect.width(),
                                         (Rect().height() - CompassesSharpRectangleHeight)/2,
                                         CompassesSharpRectangleWidth,
                                         CompassesSharpRectangleHeight);

    CompassesPenPointRect = QRectF(Rect().width() - CompassesPenPointWidth,
                                   (Rect().height() - CompassesPenPointHeight/2)/2,
                                   CompassesPenPointWidth,
                                   CompassesPenPointHeight);
    CompassesPenPointRectangleRect = QRectF(CompassesPenPointRect.x() - CompassesPenPointRectangleWidth,
                                            (Rect().height() - CompassesPenPointRectangleHeight)/2,
                                            CompassesPenPointRectangleWidth,
                                            CompassesPenPointRectangleHeight);

    qreal CompassesOutriggerWidth = Rect().width() - CompassesSharpWidth
                                                   - CompassesSharpRectangleWidth
                                                   - CompassesPenPointWidth
                                                   - CompassesPenPointRectangleWidth;
    CompassesOutriggerRect = QRectF(CompassesSharpRectangleRect.topRight().rx(),
                                    (Rect().height() - CompassesOutriggerHeight)/2,
                                    CompassesOutriggerWidth,
                                    CompassesOutriggerHeight);

    qreal CompassesSpindleX = CompassesOutriggerRect.x() + (CompassesOutriggerRect.width()
                                                         - CompassesSpindleWidth)/2;
    CompassesSpindleRect = QRectF(CompassesSpindleX,
                                  0,
                                  CompassesSpindleWidth,
                                  CompassesSpindleHeight);

    SetOriginPos(QPointF(0, (Rect().height() - CompassesBorderWidth)/2));
    this->setTransformOriginPoint(OriginPos());

    SetResizeButtonSvg(":/TeachingTool/svg/resizeCompass.svg");
    m_pResizeButton->setVisible(false);
    SetCloseButtonSvg(":/TeachingTool/svg/closeTool.svg");
    m_pCloseButton->setVisible(false);

    UpdateResizeCursor();

}

void TeachingToolCompass::UpdateResizeCursor()
{
    QPixmap pix(":/TeachingTool/png/resize.png");
    QTransform tr;
    tr.rotate(360 - angleInDegrees());
    ResizeCursor  = QCursor(pix.transformed(tr, Qt::SmoothTransformation), pix.width() / 2,  pix.height() / 2);
}

void TeachingToolCompass::UpdatePenCircleCursor()
{
    QPixmap pix(":/TeachingTool/png/drawCompass.png");
    QTransform tr;
    tr.rotate(360 - angleInDegrees());
    PenCircleCursor  = QCursor(pix.transformed(tr, Qt::SmoothTransformation), pix.width() / 2,  pix.height() / 2);
}

void TeachingToolCompass::SetCursor(QCursor cursor)
{
    if(CurrentView != nullptr)
    {
        QGraphicsView *view = CurrentView(this->scene());
        view->setCursor(cursor);
    } else {
        setCursor(cursor);
    }
}

void TeachingToolCompass::PaintCompassesSharp(QPainter *painter)
{
    painter->save();
    QPen pen;
    pen.setCapStyle(Qt::RoundCap);
    pen.setColor(CompassesSharpColor);
    pen.setWidthF(CompassesSharpRect.height());
    painter->setPen(pen);
    painter->drawPath(CompassesSharpPath());
    painter->restore();
}

void TeachingToolCompass::PaintCompassesSharpRectangle(QPainter *painter)
{
    painter->save();
    QPen pen;
    pen.setColor(CompassesBorderColor);
    pen.setWidthF(CompassesBorderWidth);
    painter->setPen(pen);
    painter->setBrush(QBrush(CompassesSharpRectangleColor));
    painter->drawPath(CompassesSharpRectanglePath());
    painter->restore();
}

void TeachingToolCompass::PaintCompassesOutrigger(QPainter *painter)
{
    painter->save();
    QPen pen;
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setColor(CompassesBorderColor);
    pen.setWidthF(CompassesBorderWidth);
    painter->setPen(pen);
    painter->setBrush(QBrush(CompassesOutriggerColor));
    painter->drawPath(CompassesOutriggerPath());
    painter->restore();
}

void TeachingToolCompass::PaintCompassesSpindle(QPainter *painter)
{
    painter->save();
    QPen pen;
    pen.setColor(CompassesBorderColor);
    pen.setWidthF(CompassesBorderWidth);
    painter->setPen(pen);
    painter->setBrush(QBrush(CompassesSpindleRectangleColor));
    painter->drawPath(CompassesSpindleRectanglePath());

    painter->setBrush(CompassesSpindleRoundnessColor);
    painter->drawPath(CompassesSpindleCirclePath());

    // 画字
    qreal rotation = 0;
    if(GetState() == TEAHINGTOOL_STATE_PEN)
    {
        rotation = -SpanAngleInDegrees;
    } else {
        rotation = 360 - angleInDegrees();
    }
    if(rotation > 5000)
    {
        rotation = 0;
    }
    if(GetState() != TEAHINGTOOL_STATE_NONE && GetState() != TEAHINGTOOL_STATE_DORMANCY)
    {

        QString angle = QString("%1°").arg(QString::number(rotation, 'f', 1));
        QFont font = painter->font();
        font.setPixelSize(11);
        painter->setFont(font);
        QFontMetrics fm(font);
        int pixelsWide = fm.horizontalAdvance(angle);
        //fm.height();
        painter->setPen(CompassesTextColor);
        if(angleInDegrees() > 270.0 || angleInDegrees() < 90)
        {
            painter->translate(QPointF(Rect().width()/2, Rect().height()/2 - 4));
        } else {
            painter->translate(QPointF(Rect().width()/2, Rect().height()/2));
        }
        painter->rotate(angleInDegrees());
        painter->drawText(QPointF(-(pixelsWide/2) + 4, fm.height()/2 + 1), angle);
    }
    painter->restore();
}

void TeachingToolCompass::PaintCompassesPenPointRectangle(QPainter *painter)
{
    painter->save();
    QPen pen;
    pen.setColor(CompassesBorderColor);
    pen.setWidthF(CompassesBorderWidth);
    painter->setPen(pen);
    painter->setBrush(QBrush(CompassesPenPointRectangleColor));
    painter->drawPath(CompassesPenPointRectanglePath());
    painter->restore();
}

void TeachingToolCompass::PaintCompassesPenPoint(QPainter *painter)
{
    painter->save();
    QPen pen;
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidthF(CompassesPenPointRect.height());
    painter->setPen(pen);
    painter->drawPath(CompassesPenPointPath());
    painter->restore();
}

void TeachingToolCompass::PaintCompassesLine(QPainter *painter)
{
    painter->save();
    QFont font = painter->font();
    font.setPixelSize(12);
    painter->setFont(font);
    QFontMetrics fm(font);
    QString linetext = QString("%1cm").arg(QString::number(CatMath::PxtoCm(Rect().width()), 'f', 1));
    int pixelsWide = fm.horizontalAdvance(linetext);
    painter->setPen(QColor(CompassesTextColor));
    if(angleInDegrees() > 270.0 || angleInDegrees() < 90)
    {
        painter->translate(QPointF(ResizeButtonRect().x() - pixelsWide - 4, (Rect().height() - fm.height()/2)/2 + 4.5));
    } else {
        painter->translate(QPointF(ResizeButtonRect().x() - 4, (Rect().height() - fm.height()/2)/2 - 4));
        painter->rotate(180);
    }
    painter->drawText(QPointF(0, 0), linetext);
    painter->restore();
}

void TeachingToolCompass::PaintButton()
{
    m_pResizeButton->setPos(ResizeButtonRect().x(), ResizeButtonRect().y());

    m_pCloseButton->setPos(CloseButtonRect().x(), CloseButtonRect().y());
}

void TeachingToolCompass::rotateAroundNeedle(qreal angle)
{
    QTransform transform;
    transform.translate(OriginPos().x(), OriginPos().y());
    CurrentAngle = angle;
    transform.rotate(angle);
    transform.translate(- OriginPos().x(), - OriginPos().y());
    setTransform(transform, true);
}

qreal TeachingToolCompass::angleInDegrees() const
{
    QRectF itemRect = boundingRect();
    QTransform itemTransform = sceneTransform();
    QPointF topLeft = itemTransform.map(itemRect.topLeft());
    QPointF topRight = itemTransform.map(itemRect.topRight());
    QLineF topLine(topLeft, topRight);
    return topLine.angle();
}

QRectF TeachingToolCompass::CloseButtonRect() const
{
    QPixmap pixmap(CloseButtonSvg);
    QSizeF size(pixmap.rect().width(),
                pixmap.rect().height());
    QPointF topleft(CompassesSharpRectangleRect.width() + CompassesSharpRect.width() + 2,
                    (Rect().height() - size.rheight())/2 - CompassesBorderWidth);
    return QRectF(topleft, size);
}

QRectF TeachingToolCompass::ResizeButtonRect() const
{
    QPixmap pixmap(ResizeButtonSvg);
    QSizeF size(pixmap.rect().width(),
                pixmap.rect().height());
    QPointF topleft(Rect().width() - CompassesPenPointRectangleRect.width() - CompassesPenPointRect.width() - size.rwidth() - 2,
                    (Rect().height() - size.rheight())/2 - CompassesBorderWidth);
    return QRectF(topleft, size);
}

QPainterPath TeachingToolCompass::CompassesSharpPath() const
{
    QPainterPath path;
    path.moveTo(CompassesSharpRect.x(), CompassesSharpRect.y());
    path.lineTo(CompassesSharpRect.width(), CompassesSharpRect.y());
    return path;
}

QPainterPath TeachingToolCompass::CompassesSharpRectanglePath() const
{
    QPainterPath path;
    path.addRoundedRect(QRectF(QPointF(CompassesSharpRectangleRect.x(),
                                       CompassesSharpRectangleRect.y() - CompassesBorderWidth),
                               CompassesSharpRectangleRect.size()),
                        CompassesSharpRectangleBorderRadius,
                        CompassesSharpRectangleBorderRadius);
    return path;
}

QPainterPath TeachingToolCompass::CompassesOutriggerPath() const
{
    QPainterPath path;
    path.addRoundedRect(QRectF(CompassesOutriggerRect.x(),
                               CompassesOutriggerRect.y() - CompassesBorderWidth,
                               CompassesOutriggerRect.width(),
                               CompassesOutriggerRect.height()),
                        CompassesOutriggerBorderRadius,
                        CompassesOutriggerBorderRadius);
    return path;
}

QPainterPath TeachingToolCompass::CompassesSpindleRectanglePath() const
{
    QPainterPath path;
    path.addRoundedRect(QRectF(CompassesSpindleRect.x(),
                               CompassesSpindleRect.y() - CompassesBorderWidth,
                               CompassesSpindleRect.width(),
                               CompassesSpindleRect.height()),
                        CompassesOutriggerBorderRadius,
                        CompassesOutriggerBorderRadius);
    return path;
}

QPainterPath TeachingToolCompass::CompassesSpindleCirclePath() const
{
    QPainterPath path;
    qreal back = 5;
    path.addEllipse(QRectF(CompassesSpindleRect.x() + back/2,
                           CompassesSpindleRect.y() - CompassesBorderWidth + back/2,
                           CompassesSpindleRect.width() - back,
                           CompassesSpindleRect.height() - back));
    return path;
}

QPainterPath TeachingToolCompass::CompassesPenPointRectanglePath() const
{
    QPainterPath path;
    path.addRoundedRect(QRectF(QPointF(CompassesPenPointRectangleRect.x(),
                                       CompassesPenPointRectangleRect.y() - CompassesBorderWidth),
                                        CompassesPenPointRectangleRect.size()),
                                        CompassesPenPointRectangleBorderRadius,
                                        CompassesPenPointRectangleBorderRadius);
    return path;
}

QPainterPath TeachingToolCompass::CompassesPenPointPath() const
{
    QPainterPath path;
    path.moveTo(QPointF(CompassesPenPointRect.x(),
                        CompassesPenPointRect.y()));
    path.lineTo(Rect().width(), CompassesPenPointRect.y());
    return path;
}

void TeachingToolCompass::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && GetState() != TEAHINGTOOL_STATE_DORMANCY)
    {
        QPointF pos = event->pos();
        if(CloseButtonRect().contains(pos))
        {
            SetState(TEAHINGTOOL_STATE_CLOSE);
            m_pResizeButton->setVisible(false);
        } else if(CompassesSpindleRectanglePath().contains(pos))
        {
            SetState(TEAHINGTOOL_STATE_ROTATE);
            m_pResizeButton->setVisible(false);
            m_pCloseButton->setVisible(false);
            SetPressPos(pos);
        } else if(ResizeButtonRect().contains(pos))
        {
            SetState(TEAHINGTOOL_STATE_RESIZE_ONE);
            m_pCloseButton->setVisible(false);
            SetPressPos(pos);
        } else if(CompassesPenPointRectanglePath().contains(pos)) {
            SetState(TEAHINGTOOL_STATE_PEN);
            m_pResizeButton->setVisible(false);
            m_pCloseButton->setVisible(false);
            SetPressPos(pos);
            SpanAngleInDegrees = 0;

            QPointF CenterPos = CatMath::PointCoordinatesOnACircle(this->scenePos(), OriginPos().y(), (360 - angleInDegrees()) + 90);
            QPointF startpos = CatMath::PointCoordinatesOnACircle(CenterPos, Rect().width(), (360 - angleInDegrees()));
            emit ArcStart(QRectF(CenterPos.rx() - Rect().width(),
                                 CenterPos.ry() - Rect().width(),
                                 Rect().width()*2.0,
                                 Rect().width()*2.0),
                          angleInDegrees());
            emit ArcStartPos(startpos);
            //qDebug() << "angleInDegrees: " << angleInDegrees();
            prepareGeometryChange();
        } else if(boundingRect().contains(pos))
        {
            SetState(TEAHINGTOOL_STATE_MOVE);
            m_pCloseButton->setVisible(false);
            m_pResizeButton->setVisible(false);
            SetPressPos(event->scenePos());
        }
    }
}

void TeachingToolCompass::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(GetState() != TEAHINGTOOL_STATE_DORMANCY)
    {
        switch (GetState()) {
            case TEAHINGTOOL_STATE_MOVE: {
                QPointF pos = event->scenePos();
                QPointF move = pos - PressPos();
                this->moveBy(move.rx(), move.ry());
                SetPressPos(pos);
                break;
            }
            case TEAHINGTOOL_STATE_RESIZE_ONE: {
                QPointF pos = event->pos();
                QPointF size = pos - PressPos();
                qreal width = Rect().width() + size.rx();
                if(width < MinRect().width())
                {
                    SetRect(MinRect());
                } else if(width > MaxRect().width())
                {
                    SetRect(MaxRect());
                } else {
                    SetRect(QRectF(Rect().x(), Rect().y(), width, Rect().height()));

                }
                CompassesPenPointRect = QRectF(Rect().width() - CompassesPenPointWidth,
                                               (Rect().height() - CompassesPenPointHeight/2)/2,
                                               CompassesPenPointWidth,
                                               CompassesPenPointHeight);
                CompassesPenPointRectangleRect = QRectF(CompassesPenPointRect.x() - CompassesPenPointRectangleWidth,
                                                        (Rect().height() - CompassesPenPointRectangleHeight)/2,
                                                        CompassesPenPointRectangleWidth,
                                                        CompassesPenPointRectangleHeight);

                qreal CompassesOutriggerWidth = Rect().width() - CompassesSharpWidth
                                                               - CompassesSharpRectangleWidth
                                                               - CompassesPenPointWidth
                                                               - CompassesPenPointRectangleWidth;
                CompassesOutriggerRect = QRectF(CompassesSharpRectangleRect.topRight().rx(),
                                                (Rect().height() - CompassesOutriggerHeight)/2,
                                                CompassesOutriggerWidth,
                                                CompassesOutriggerHeight);
                qreal CompassesSpindleX = CompassesOutriggerRect.x() + (CompassesOutriggerRect.width()
                                                                     - CompassesSpindleWidth)/2;
                CompassesSpindleRect = QRectF(CompassesSpindleX,
                                              0,
                                              CompassesSpindleWidth,
                                              CompassesSpindleHeight);
                SetPressPos(pos);
                break;
            }
            case TEAHINGTOOL_STATE_ROTATE: {
                QLineF currentLine(OriginPos(), event->pos());
                QLineF lastLine(OriginPos(), event->lastPos());
                qreal deltaAngle = currentLine.angleTo(lastLine);
                if (deltaAngle > 180)
                    deltaAngle -= 360;
                else if (deltaAngle < -180)
                    deltaAngle += 360;
                rotateAroundNeedle(deltaAngle);
                UpdatePenCircleCursor();
                UpdateResizeCursor();
                break;
            }
            case TEAHINGTOOL_STATE_PEN: {

                // 判断绘制是顺时针还是逆时针
                QLineF currentLine(OriginPos(), event->pos());
                QLineF lastLine(OriginPos(), event->lastPos());
                qreal deltaAngle = currentLine.angleTo(lastLine);
                if (deltaAngle > 180)
                    deltaAngle -= 360;
                else if (deltaAngle < -180)
                    deltaAngle += 360;
                rotateAroundNeedle(deltaAngle);

                SpanAngleInDegrees += deltaAngle;
                if (SpanAngleInDegrees >= 1080)
                    SpanAngleInDegrees -= 360;
                else if (SpanAngleInDegrees < -1080)
                    SpanAngleInDegrees += 360;
                emit ArcUpdate(-SpanAngleInDegrees);
                QPointF CenterPos = CatMath::PointCoordinatesOnACircle(this->scenePos(), OriginPos().y(), (360 - angleInDegrees()) + 90);
                QPointF updatepos = CatMath::PointCoordinatesOnACircle(CenterPos, Rect().width(), (360 - angleInDegrees()));
                emit ArcUpdatePos(updatepos);

                UpdatePenCircleCursor();
                UpdateResizeCursor();
                SetCursor(PenCircleCursor);
                break;
            }
            default:{
                break;
            }
        }
        prepareGeometryChange();
    }
}

void TeachingToolCompass::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    if(GetState() != TEAHINGTOOL_STATE_DORMANCY)
    {
        if(GetState() == TEAHINGTOOL_STATE_CLOSE)
        {
            SetState(TEAHINGTOOL_STATE_NONE);
            emit Closeed();
            this->deleteLater();
        } if(GetState() == TEAHINGTOOL_STATE_PEN) {
            SetState(TEAHINGTOOL_STATE_NONE);
            emit ArcEnd();
            emit ArcEndPos();
        } else {
            SetState(TEAHINGTOOL_STATE_NONE);
            m_pResizeButton->setVisible(true);
            m_pCloseButton->setVisible(true);
            prepareGeometryChange();
        }
    }
}

void TeachingToolCompass::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if(GetState() != TEAHINGTOOL_STATE_DORMANCY)
    {
        QPointF pos = event->pos();

        if(CompassesSpindleRectanglePath().contains(pos))
        {
            SetCursor(RotateCursor);
            SetState(TEAHINGTOOL_STATE_ROTATE);
            prepareGeometryChange();
            return;
        }
        if(CloseButtonRect().contains(pos))
        {
            SetCursor(CloseCursor);
            SetState(TEAHINGTOOL_STATE_CLOSE);
            prepareGeometryChange();
            return;
        }
        if(ResizeButtonRect().contains(pos))
        {
            SetCursor(ResizeCursor);
            SetState(TEAHINGTOOL_STATE_RESIZE_ONE);
            prepareGeometryChange();
            return;
        }

        if(CompassesPenPointRectanglePath().contains(pos) ||
           CompassesPenPointPath().contains(pos))
        {
            SetCursor(PenCircleCursor);
            SetState(TEAHINGTOOL_STATE_NONE);
            prepareGeometryChange();
            return;
        }
        if(CompassesSharpPath().contains(pos) ||
            CompassesOutriggerPath().contains(pos) ||
            CompassesSharpRectanglePath().contains(pos))
        {
            SetCursor(MoveCursor);
            SetState(TEAHINGTOOL_STATE_MOVE);
            prepareGeometryChange();
            return;
        }
    }
}

void TeachingToolCompass::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)
    if(GetState() != TEAHINGTOOL_STATE_DORMANCY)
    {
        emit HoverEntered();
        m_pResizeButton->setVisible(true);
        m_pCloseButton->setVisible(true);
    }
}

void TeachingToolCompass::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)
    if(GetState() != TEAHINGTOOL_STATE_DORMANCY)
    {
        emit HoverLeaveed();
        SetState(TEAHINGTOOL_STATE_NONE);
        m_pResizeButton->setVisible(false);
        m_pCloseButton->setVisible(false);
        SetCursor(Qt::ArrowCursor);
        prepareGeometryChange();
    }
}
