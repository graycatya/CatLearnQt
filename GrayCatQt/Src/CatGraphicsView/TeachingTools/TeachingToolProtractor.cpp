#pragma execution_character_set("utf-8")
#include "TeachingToolProtractor.h"
#include <QGraphicsSvgItem>
#include <QPainter>
#include <QPainterPath>
#include <QGraphicsSceneHoverEvent>
#include <QCursor>
#include <QGraphicsView>
#include "CatMath.h"

#include <QDebug>

const QRectF DefaultRect = QRectF(0, 0, 500, 500);
const QRectF TeachingToolProtractor::sDefaultRect = DefaultRect;
const qreal angleButtonSize = 40;
const qreal AxleCircle = 90;
const qreal minRadius = 250;

// 测量角度用的Item
class ProtractorAngle : public QGraphicsItem
{

public:
    explicit ProtractorAngle(QGraphicsItem *parent = nullptr)
        : QGraphicsItem(parent)
    {
        setParentItem(parent);
        InitProperty();
    }

    ~ProtractorAngle(){

    }

    inline bool GetRotate( void ) const { return Rotate; }

    inline QString GetAngleButtonSvg() const { return AngleButtonSvg; }

    QRectF boundingRect() const
    {
        QRectF rectf = QRectF(-angleButtonSize, -angleButtonSize,
                              DefaultRect.width() + angleButtonSize*2,
                              DefaultRect.height() + angleButtonSize*2);
        return rectf;
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget)
    {
        Q_UNUSED(option)
        Q_UNUSED(widget)
        painter->setRenderHint(QPainter::Antialiasing, true);
        painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
        painter->setRenderHint(QPainter::TextAntialiasing, true);

        PaintButton();
    }
    QPainterPath shape() const
    {
        QPainterPath path;
        path.addRect(AngleButtonRect());
        return path;
    }

    QRectF AngleButtonRect() const
    {
        QPixmap pixmap(AngleButtonSvg);
        QSizeF size(pixmap.rect().width(),
                    pixmap.rect().height());
        QPointF topleft(DefaultRect.width() + 5,
                        DefaultRect.height()/2 -(size.height()/2));
        return QRectF(topleft, size);
    }

    void SetAngleButtonSvg(QString svg)
    {
        if(AngleButtonSvg != svg || m_pAngleButton == nullptr)
        {
            if(m_pAngleButton != nullptr)
            {
                m_pAngleButton->deleteLater();
                m_pAngleButton = nullptr;
            }
            AngleButtonSvg = svg;
            m_pAngleButton = new QGraphicsSvgItem(svg, this);
            prepareGeometryChange();
        }
    }

private:
    void InitProperty( void )
    {
        m_yOriginPos = QPointF(DefaultRect.width()/2, DefaultRect.height()/2);
        this->setTransformOriginPoint(m_yOriginPos);
        SetAngleButtonSvg(":/TeachingTool/svg/angleMarker.svg");
    }

    void PaintButton()
    {
        m_pAngleButton->setPos(AngleButtonRect().x(), AngleButtonRect().y());
    }

     bool State( void )
     {
         TeachingToolProtractor *m_pTeachingToolProtractor = dynamic_cast<TeachingToolProtractor*>(this->parentItem());
         if(m_pTeachingToolProtractor->GetState() == AbsTeachingTool::TEAHINGTOOL_STATE_PEN
                 || m_pTeachingToolProtractor->GetState() == AbsTeachingTool::TEAHINGTOOL_STATE_DORMANCY)
         {
            return false;
         }
         return true;
     }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
        if(event->button() == Qt::LeftButton && State())
        {
            if(AngleButtonRect().contains(event->pos()))
            {
                Rotate = true;
                m_yPressPos = event->pos();
            }
        }
    }

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event)
    {
        if(Rotate)
        {
            QPointF pos = event->pos();
            QVector2D Start = QVector2D(m_yPressPos - this->transformOriginPoint());
            QVector2D End = QVector2D(pos - this->transformOriginPoint());

            qreal angle = 0.0;
            qreal angleEnd = CatMath::DegreeAngle(End);
            qreal angleStart = CatMath::DegreeAngle(Start);
            angle = angleEnd - angleStart + rotation();

            angle = CatMath::AngleJudge(angle);

            if(this->rotation() < 270.0 && this->rotation() >= 180.0)
            {
                if(angle > 0 && angle <= 180)
                {
                    angle = 180.0;
                }
            } else if((this->rotation() < 360.0
                       && this->rotation() > 270.0)
                      || this->rotation() == 0.0)
            {
                if(angle > 0 && angle < 180)
                {
                    angle = 0.0;
                }
            }
            setRotation(angle);

            this->parentItem()->update();
        }
    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
    {
        Q_UNUSED(event)
        if(State())
        {
            Rotate = false;
            this->parentItem()->update();
        }
    }

    void hoverMoveEvent(QGraphicsSceneHoverEvent *event)
    {
        Q_UNUSED(event)
        if(State())
        {
            this->parentItem()->update();
        }
    }

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event)
    {
        Q_UNUSED(event)
        if(State())
        {
            this->parentItem()->update();
        }
    }

    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
    {
        Q_UNUSED(event)
        if(State())
        {
            this->parentItem()->update();
        }
    }

private:
    bool Rotate = false;
    bool Anticlockwise = false;
    qreal LastTimeAngle = 0.0;
    QString AngleButtonSvg = ":/TeachingTool/svg/angleMarker.svg";
    QGraphicsSvgItem *m_pAngleButton = nullptr;           // 量角按钮
    // 鼠标按下坐标
    QPointF m_yPressPos = QPointF(0,0);
    // 原点
    QPointF m_yOriginPos = QPointF(0,0);
};

TeachingToolProtractor::TeachingToolProtractor()
{
    InitProperty();
}

TeachingToolProtractor::~TeachingToolProtractor()
{

}

QRectF TeachingToolProtractor::boundingRect() const
{
    QRectF rectf = QRectF(-angleButtonSize, -angleButtonSize,
                          this->rect().width() + angleButtonSize*2,
                          this->rect().height() + angleButtonSize*2);
    return rectf;
}

void TeachingToolProtractor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter->setRenderHint(QPainter::TextAntialiasing, true);

    // [0] 绘制量角器背景
    PaintBackground(painter);
    // [1] 绘制量角器刻度
    PaintScale(painter);
    // [2] 绘制量角轴
    PaintProtractorAxis(painter);
    // [3] 绘制按钮
    PaintButton();
}

QPainterPath TeachingToolProtractor::shape() const
{
    QPainterPath path;
    //path.setFillRule(Qt::WindingFill);
    path.addPath(ProtractorBackgroundPath());
    path.addRect(QRectF(CloseButtonRect().x(),
                        CloseButtonRect().y() + CloseButtonRect().height()/2,
                        CloseButtonRect().width(),
                        CloseButtonRect().height()/2));
    path.addRect(QRectF(ResizeButtonRect().x(),
                 ResizeButtonRect().y() + ResizeButtonRect().height()/2,
                 ResizeButtonRect().width(),
                 ResizeButtonRect().height()/2));
    path.addRect(QRectF(RestButtonRect().x(),
                 RestButtonRect().y() + RestButtonRect().height()/2,
                 RestButtonRect().width(),
                 RestButtonRect().height()/2));
    return path;
}

void TeachingToolProtractor::SetCloseButtonSvg(QString svg)
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

void TeachingToolProtractor::SetResizeButtonSvg(QString svg)
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

void TeachingToolProtractor::SetRotateButtonSvg(QString svg)
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

void TeachingToolProtractor::SetRestButtonSvg(QString svg)
{
    if(RestButtonSvg != svg)
    {
        if(m_pRestButton != nullptr)
        {
            m_pRestButton->deleteLater();
            m_pRestButton = nullptr;
        }
        RestButtonSvg = svg;
        m_pRestButton = new QGraphicsSvgItem(svg, this);
        prepareGeometryChange();
    }
}

void TeachingToolProtractor::SetProtractorBackgroundColor(QColor color)
{
    ProtractorBackgroundColor = color;
    prepareGeometryChange();
}

void TeachingToolProtractor::SetProtractorBorderColor(QColor color)
{
    ProtractorBorderColor = color;
    prepareGeometryChange();
}

void TeachingToolProtractor::SetProtractorTextColor(QColor color)
{
    ProtractorTextColor = color;
    prepareGeometryChange();
}

void TeachingToolProtractor::SetProtractorScaleColor(QColor color)
{
    ProtractorScaleColor = color;
    prepareGeometryChange();
}

void TeachingToolProtractor::SetProtractorAxleColor(QColor color)
{
    ProtractorAxleColor = color;
    prepareGeometryChange();
}

void TeachingToolProtractor::InitProperty()
{
    RotateCursor = QCursor(QPixmap(":/TeachingTool/png/rotate.png"), 16, 16);
    ResizeCursor = QCursor(QPixmap(":/TeachingTool/png/resize.png"), 16, 16);
    MoveCursor = QCursor(Qt::SizeAllCursor);
    CloseCursor = QCursor(Qt::ArrowCursor);

    m_pProtractorAngle = new ProtractorAngle(this);
    m_pProtractorAngle->setPos(this->pos());

    setAcceptHoverEvents(true);

    setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    SetRect(QRectF(0, 0, sDefaultRect.width(), sDefaultRect.height()));

    this->setRect(Rect());

    ProtractorBorderWidth = 1;

    ProtractorBackgroundColor = QColor(234, 242, 244, 204);
    ProtractorBorderColor = QColor(102, 102, 102);
    ProtractorScaleColor = QColor(102, 102, 102);
    ProtractorTextColor = QColor(102, 102, 102);
    ProtractorAxleColor = QColor(102, 102, 102);

    mScaleFactor = 1;

    setStartAngle(0);
    setSpanAngle(180 * 16);

    SetOriginPos(QPointF(rect().width()/2, rect().height()/2));
    this->setTransformOriginPoint(OriginPos());

    SetRestButtonSvg(":/TeachingTool/svg/resetTool.svg");
    m_pRestButton->setVisible(false);
    SetCloseButtonSvg(":/TeachingTool/svg/closeTool.svg");
    m_pCloseButton->setVisible(false);
    SetRotateButtonSvg(":/TeachingTool/svg/rotateTool.svg");
    m_pRotateButton->setVisible(false);
    SetResizeButtonSvg(":/TeachingTool/svg/resizeTool.svg");
    m_pResizeButton->setVisible(false);


}

QRectF TeachingToolProtractor::CloseButtonRect() const
{
    QPixmap pixmap(CloseButtonSvg);
    QSizeF size(pixmap.rect().width(),
                pixmap.rect().height());
    QPointF topleft(size.width(),
                    (rect().height() - size.height())/2);
    return QRectF(topleft, size);
}

QRectF TeachingToolProtractor::ResizeButtonRect() const
{
    QPixmap pixmap(ResizeButtonSvg);
    QSizeF size(pixmap.rect().width(),
                pixmap.rect().height());
    QPointF topleft(rect().width() - size.width()*2,
                    (rect().height() - size.height())/2);
    return QRectF(topleft, size);
}

QRectF TeachingToolProtractor::RotateButtonRect() const
{
    QPixmap pixmap(RotateButtonSvg);
    QSizeF size(pixmap.rect().width(),
                pixmap.rect().height());
    QPointF topleft(rect().width() - size.width()*4 - size.width()/5,
                    rect().height()/2 - size.height()*5 - size.height()/3);
    return QRectF(topleft, size);
}

QRectF TeachingToolProtractor::RestButtonRect() const
{
    QPixmap pixmap(RestButtonSvg);
    QSizeF size(pixmap.rect().width(),
                pixmap.rect().height());
    QPointF topleft(CloseButtonRect().x() + size.width() + size.width()/2,
                    (rect().height() - size.height())/2);
    return QRectF(topleft, size);
}

void TeachingToolProtractor::UpdateResizeCursor()
{
    QPixmap pix(":/TeachingTool/png/resize.png");
    QTransform tr;
    tr.rotate(this->rotation());
    ResizeCursor  = QCursor(pix.transformed(tr, Qt::SmoothTransformation), pix.width() / 2,  pix.height() / 2);
}

void TeachingToolProtractor::SetCursor(QCursor cursor)
{
    if(CurrentView != nullptr)
    {
        QGraphicsView *view = CurrentView(this->scene());
        view->setCursor(cursor);
    } else {
        setCursor(cursor);
    }
}

void TeachingToolProtractor::PaintBackground(QPainter *painter)
{
    painter->save();

    QPen pen_(ProtractorBorderColor);
    pen_.setWidthF(ProtractorBorderWidth);
    painter->setPen(pen_);
    painter->setBrush(ProtractorBackgroundColor);
    painter->drawPath(ProtractorBackgroundPath());

    painter->restore();
}

void TeachingToolProtractor::PaintScale(QPainter *painter)
{
    painter->save();
    // [0] 绘制中轴线
    painter->save();
    QPen penLine;
    penLine.setWidthF(ProtractorBorderWidth);
    penLine.setColor(ProtractorAxleColor);
    painter->setPen(penLine);
    painter->drawLine(QPointF(rect().width()/2, rect().height()/2),
                      QPointF(rect().width()/2, rect().height()/2 - 40.0));
    painter->restore();

    // [1] 绘制内圆
    painter->save();
    QPen penInnercircle;
    penInnercircle.setWidthF(ProtractorBorderWidth);
    penInnercircle.setColor(ProtractorAxleColor);
    painter->setPen(penInnercircle);
    painter->translate(QPointF(rect().width()/4, rect().height()/4));
    painter->drawArc(QRectF(0, 0,
                            rect().width()/2, rect().height()/2),
                     0 * 16, 180 * 16);
    painter->restore();

    // [2] 绘制 圆刻度 数字
    for(qreal angle_init = 1;angle_init < 180; angle_init++)
    {
        int lineWidth = 0;

        // 绘制刻度
        painter->save();
        painter->translate(QPointF(rect().width()/2, rect().height()/2));
        painter->rotate(-angle_init);

        if((static_cast<int>(angle_init)%10) == 0)
        {
            lineWidth = 32;

        } else if((static_cast<int>(angle_init)%5) == 0)
        {
            lineWidth = 24;
        } else {
            lineWidth = 8;
        }

        QPen penScaleLine;
        penScaleLine.setWidthF(1);
        penScaleLine.setColor(ProtractorScaleColor);
        painter->setPen(penScaleLine);

        painter->drawLine(QPointF(rect().width()/2 - lineWidth, 0),
                          QPointF(rect().width()/2, 0));

        painter->drawLine(QPointF(rect().width()/4, 0),
                          QPointF(rect().width()/4 + lineWidth, 0));
        painter->restore();



        // 外圆刻度数字
        painter->save();
        painter->translate(QPointF(rect().width()/2, rect().height()/2));
        painter->rotate(-angle_init);

        if((static_cast<int>(angle_init)%10) == 0)
        {
            QString linetext = QString("%1").arg(QString::number(angle_init, 'f', 0));
            QFont font1 = painter->font();
            font1.setPixelSize(16);
            painter->setFont(font1);
            painter->setPen(ProtractorBorderColor);
            QFontMetrics fm1(font1);
            int pixelsWide1 = fm1.horizontalAdvance(linetext);
            //qDebug() << "font size: " << pixelsWide1 << " : " << fm1.height();
            painter->translate(QPointF(rect().width()/2 - lineWidth - pixelsWide1/2,
                                       0));
            painter->rotate(angle_init);
            if(angle_init >= 100 && angle_init <= 120)
            {
                painter->drawText(QRectF(- pixelsWide1 / 2,
                                          -(fm1.height()/2 + fm1.height()/5), pixelsWide1, fm1.height()), Qt::AlignTop, linetext);
            } else if(angle_init <= 50) {
                painter->drawText(QRectF(- pixelsWide1 / 2 - 3,
                                          -(fm1.height()/2), pixelsWide1, fm1.height()), Qt::AlignTop, linetext);
            } else {
                painter->drawText(QRectF(- pixelsWide1 / 2,
                                          -(fm1.height()/2), pixelsWide1, fm1.height()), Qt::AlignTop, linetext);
            }
        }
        painter->restore();

        // 内圆刻度数字
        painter->save();
        painter->translate(QPointF(rect().width()/2, rect().height()/2));
        painter->rotate(-angle_init);

        if((static_cast<int>(angle_init)%10) == 0)
        {
            QString linetext = QString("%1").arg(QString::number(180-angle_init, 'f', 0));
            QFont font2 = painter->font();
            font2.setPixelSize(12);
            painter->setFont(font2);
            painter->setPen(ProtractorTextColor);
            QFontMetrics fm2(font2);
            int pixelsWide2 = fm2.horizontalAdvance(linetext);
            painter->translate(QPointF(rect().width()/4 + pixelsWide2/2 + lineWidth,
                                       0));
            painter->rotate(angle_init);
            if(angle_init <= 60)
            {
                painter->drawText(QRectF(- pixelsWide2 / 2 + fm2.height()/4,
                                          -(fm2.height()/2), pixelsWide2, fm2.height()), Qt::AlignTop, linetext);
            } else if(angle_init >= 120)
            {
                painter->drawText(QRectF(- pixelsWide2 / 2 - fm2.height()/4,
                                          -(fm2.height()/2), pixelsWide2, fm2.height()), Qt::AlignTop, linetext);
            } else {
                painter->drawText(QRectF(- pixelsWide2 / 2,
                                          -(fm2.height()/2), pixelsWide2, fm2.height()), Qt::AlignTop, linetext);
            }

        }
        painter->restore();

    }
    painter->restore();
}

void TeachingToolProtractor::PaintProtractorAxis(QPainter *painter)
{
    painter->save();
    static qreal currentangle = 0.0;

    currentangle = m_pProtractorAngle->rotation();

    QPen pen;
    pen.setWidthF(ProtractorBorderWidth);
    pen.setColor(ProtractorAxleColor);
    painter->setPen(pen);
    painter->translate(OriginPos());
    QLineF line = QLineF(0, 0, rect().width()/2 + 5, 0);
    //mCurrentAngle = -130;
    painter->rotate(currentangle);
    painter->drawLine(line);
    painter->restore();

    painter->save();
    painter->setPen(pen);
    painter->translate(OriginPos());
    QRectF rectangle(-AxleCircle/2, -AxleCircle/2, AxleCircle, AxleCircle);
    qreal endangle = 0.0;
    if(currentangle == 0.0)
    {
        endangle = 0.0;
    } else {
        endangle = 360.0 - currentangle;
    }
    painter->drawArc(rectangle, 0 * 16, static_cast<int>(endangle) * 16);
    painter->restore();

    painter->save();
    painter->setPen(pen);
    QString ang = QString("%1°").arg(QString::number(endangle, 'f', 1));
    QString dot = QString("°");
    QFont font = painter->font();
    font.setPixelSize(18);
    font.setBold(true);
    QFontMetrics fm(font);
    int dotWide = fm.horizontalAdvance(dot);
    int pixelsWide = fm.horizontalAdvance(ang);

    painter->setFont(font);
    painter->translate(OriginPos());
    painter->translate(QPointF(0, - (AxleCircle/2 + 45) + fm.height()/2));
    painter->rotate(-this->rotation());
    painter->drawText(QRectF(-(pixelsWide/2) + dotWide/2, - fm.height()/2 ,
                             pixelsWide, fm.height()),
                      Qt::AlignVCenter | Qt::AlignHCenter, ang);
    painter->restore();
}

void TeachingToolProtractor::PaintButton()
{
    // [0] close 按钮
    m_pCloseButton->setPos(CloseButtonRect().x(), CloseButtonRect().y());
    // [1] rest 按钮
    m_pRestButton->setPos(RestButtonRect().x(), RestButtonRect().y());
    // [2] resize 按钮
    m_pResizeButton->setPos(ResizeButtonRect().x(), ResizeButtonRect().y());
    // [3] rotate 按钮
    m_pRotateButton->setPos(RotateButtonRect().x(), RotateButtonRect().y());
}

QPainterPath TeachingToolProtractor::ProtractorBackgroundPath() const
{
    QPainterPath path;
    path.moveTo(rect().width()/2, rect().height()/2);
    QRectF rectf = QRectF(0, 0, rect().width(), rect().height());
    path.arcTo(rectf, 0, 180);
    path.closeSubpath();
    return path;
}

void TeachingToolProtractor::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && GetState() != TEAHINGTOOL_STATE_DORMANCY)
    {
        this->setZValue(10);
        if(ResizeButtonRect().contains(event->pos()))
        {
            SetState(TEAHINGTOOL_STATE_RESIZE_ONE);
            m_pRotateButton->setVisible(false);
            m_pCloseButton->setVisible(false);
            m_pRestButton->setVisible(false);
            SetPressPos(event->pos());
        } else if(CloseButtonRect().contains(event->pos())) {
            SetState(TEAHINGTOOL_STATE_CLOSE);
            m_pRotateButton->setVisible(false);
            m_pRestButton->setVisible(false);
            m_pResizeButton->setVisible(false);
        } else if(RotateButtonRect().contains(event->pos())) {
            SetState(TEAHINGTOOL_STATE_ROTATE);
            m_pCloseButton->setVisible(false);
            m_pRestButton->setVisible(false);
            m_pResizeButton->setVisible(false);
            SetPressPos(event->pos());
        } else if(RestButtonRect().contains(event->pos())) {
            SetState(TEAHINGTOOL_STATE_REST);
            m_pRotateButton->setVisible(false);
            m_pCloseButton->setVisible(false);
            m_pResizeButton->setVisible(false);
        } else if(boundingRect().contains(event->pos()))
        {
            SetState(TEAHINGTOOL_STATE_MOVE);
            m_pRotateButton->setVisible(false);
            m_pCloseButton->setVisible(false);
            m_pRestButton->setVisible(false);
            m_pResizeButton->setVisible(false);
            SetPressPos(event->scenePos());
        }
    }
}

void TeachingToolProtractor::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
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
            case TEAHINGTOOL_STATE_ROTATE:{
                QPointF pos = event->pos();
                QVector2D Start = QVector2D(PressPos() - this->transformOriginPoint());
                QVector2D End = QVector2D(pos - this->transformOriginPoint());

                qreal angle = 0.0;
                qreal angleEnd = CatMath::DegreeAngle(End);
                qreal angleStart = CatMath::DegreeAngle(Start);
                angle = angleEnd - angleStart + rotation();
                angle = CatMath::AngleJudge(angle);
                setRotation(angle);
                UpdateResizeCursor();
                break;
            }
            case TEAHINGTOOL_STATE_RESIZE_ONE: {
                QPointF pos = event->pos();
                QLineF startLine(rect().center(), PressPos());
                QLineF currentLine(rect().center(), pos);
                qreal scaleFactor = currentLine.length()/startLine.length();
                if (radius() * mScaleFactor * scaleFactor > minRadius) {
                    prepareGeometryChange();
                    setTransform(QTransform::fromTranslate(rect().center().x(), rect().center().y()), true);
                    setTransform(QTransform::fromScale(scaleFactor, scaleFactor), true);
                    setTransform(QTransform::fromTranslate(-rect().center().x(), -rect().center().y()), true);
                    mScaleFactor *= scaleFactor;
                }
                break;
            }
        }
        prepareGeometryChange();
    }
}

void TeachingToolProtractor::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    if(GetState() != TEAHINGTOOL_STATE_DORMANCY)
    {
        if(GetState() == TEAHINGTOOL_STATE_CLOSE)
        {
            SetState(TEAHINGTOOL_STATE_NONE);
            emit Closeed();
            this->deleteLater();
        } if(GetState() == TEAHINGTOOL_STATE_REST) {
            SetState(TEAHINGTOOL_STATE_NONE);
            this->setRotation(0);
            m_pResizeButton->setVisible(true);
            m_pCloseButton->setVisible(true);
            m_pRotateButton->setVisible(true);
            m_pRestButton->setVisible(true);
            UpdateResizeCursor();
            prepareGeometryChange();
        } else {
            SetState(TEAHINGTOOL_STATE_NONE);
            m_pResizeButton->setVisible(true);
            m_pCloseButton->setVisible(true);
            m_pRotateButton->setVisible(true);
            m_pRestButton->setVisible(true);
            prepareGeometryChange();
        }
    }
}

void TeachingToolProtractor::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if(GetState() != TEAHINGTOOL_STATE_DORMANCY)
    {
        if(ResizeButtonRect().contains(event->pos()))
        {
            SetCursor(ResizeCursor);
        } else if(RotateButtonRect().contains(event->pos()))
        {
            SetCursor(RotateCursor);
        } else if(CloseButtonRect().contains(event->pos())
                  || RestButtonRect().contains(event->pos()))
        {
            SetCursor(CloseCursor);
        } else {
            SetCursor(MoveCursor);
        }
    }
}

void TeachingToolProtractor::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)
    if(GetState() != TEAHINGTOOL_STATE_DORMANCY)
    {
        m_pCloseButton->setVisible(true);
        m_pRestButton->setVisible(true);
        m_pRotateButton->setVisible(true);
        m_pResizeButton->setVisible(true);
        SetCursor(MoveCursor);
    }
}

void TeachingToolProtractor::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)
    if(GetState() != TEAHINGTOOL_STATE_DORMANCY)
    {
        SetState(TEAHINGTOOL_STATE_NONE);
        m_pCloseButton->setVisible(false);
        m_pRestButton->setVisible(false);
        m_pRotateButton->setVisible(false);
        m_pResizeButton->setVisible(false);
        SetCursor(Qt::ArrowCursor);
    }
}
