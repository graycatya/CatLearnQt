#include "CatGraphicsScene.h"
#include "TeachingTools/TeachingToolCompass.h"
#include "TeachingTools/TeachingToolProtractor.h"
#include "TeachingTools/TeachingToolRuler.h"
#include "TeachingTools/TeachingToolTrangle.h"
#include "CatGraphicsView.h"

#include "DrawingBoardTools/CatBrushPixItem.h"
//#include "DrawingBoardTools/CatBrushVectorPixItem.h"

#include <QGraphicsSceneMouseEvent>
#include <QPixmapCache>
#include <QDebug>
#include <QTimer>

QGraphicsView* GetView(QGraphicsScene* scene)
{
    return dynamic_cast<CatGraphicsScene*>(scene)->View();
}


CatGraphicsScene::CatGraphicsScene(QObject *parent)
    : QGraphicsScene(parent)
    , m_yView(nullptr)
    , m_pCatGraphicsObject(new CatGraphicsObject(this))
{

    //InitProperty();
}

CatGraphicsScene::~CatGraphicsScene()
{

}

void CatGraphicsScene::SetView(CatGraphicsView *view)
{
    m_yView = view;
}

CatGraphicsView *CatGraphicsScene::View()
{
    return m_yView;
}


void CatGraphicsScene::AddTeachingToolProtractor()
{
    TeachingToolProtractor *Teaching = new TeachingToolProtractor;
    this->addItem(Teaching);
    m_pTeachingToolProtractor.push_back(Teaching);
    if(m_pCatGraphicsObject->GetDrawingBoardState() == CatGraphicsObject::PEN
            || m_pCatGraphicsObject->GetDrawingBoardState() == CatGraphicsObject::ERASER)
    {
        Teaching->SetState(AbsTeachingTool::TEAHINGTOOL_STATE_DORMANCY);
    }
}

void CatGraphicsScene::AddTeachingToolRuler()
{
    TeachingToolRuler *Teaching = new TeachingToolRuler;
    Teaching->SetCurrentView(GetView);
    this->addItem(Teaching);
    m_pTeachingToolRuler.push_back(Teaching);
    connect(Teaching, &AbsTeachingTool::HoverEntered, this, [=](){
        m_pCatGraphicsObject->SetDrawingBoardState(CatGraphicsObject::CAT_DRAWINGBOARD_STATE::TeachingPen);
    });
    connect(Teaching, &AbsTeachingTool::HoverLeaveed, this, [=](){
        m_pCatGraphicsObject->SetDrawingBoardState(m_pCatGraphicsObject->GetLastDrawingBoardState());
    });
    connect(Teaching, &AbsTeachingTool::LineStartPos, this, [=](QPointF point){
        m_pCatBrushPixItem->DrawPress(1, point);
        m_yLastTeachingPoint = point;
    });
    connect(Teaching, &AbsTeachingTool::LineUpdatePos, this, [=](QPointF point){
        m_pCatBrushPixItem->DrawMove(1, m_yLastTeachingPoint, point);
        m_yLastTeachingPoint = point;
    });
    connect(Teaching, &AbsTeachingTool::LineEnd, this, [=](QPointF point){
        m_pCatBrushPixItem->DrawRelease(1, point);
        m_yLastTeachingPoint = point;
    });
    if(m_pCatGraphicsObject->GetDrawingBoardState() == CatGraphicsObject::PEN)
    {
        Teaching->SetState(AbsTeachingTool::TEAHINGTOOL_STATE_PEN);
    }
    if(m_pCatGraphicsObject->GetDrawingBoardState() == CatGraphicsObject::ERASER)
    {
        Teaching->SetState(AbsTeachingTool::TEAHINGTOOL_STATE_DORMANCY);
    }
}

void CatGraphicsScene::AddTeachingToolTrangle()
{
    TeachingToolTrangle *Teaching = new TeachingToolTrangle;
    this->addItem(Teaching);
    Teaching->SetCurrentView(GetView);
    m_pTeachingToolTrangle.push_back(Teaching);
    connect(Teaching, &AbsTeachingTool::HoverEntered, this, [=](){
        m_pCatGraphicsObject->SetDrawingBoardState(CatGraphicsObject::CAT_DRAWINGBOARD_STATE::TeachingPen);
    });
    connect(Teaching, &AbsTeachingTool::HoverLeaveed, this, [=](){
        m_pCatGraphicsObject->SetDrawingBoardState(m_pCatGraphicsObject->GetLastDrawingBoardState());
    });
    connect(Teaching, &AbsTeachingTool::LineStartPos, this, [=](QPointF point){
        m_pCatBrushPixItem->DrawPress(1, point);
        m_yLastTeachingPoint = point;
    });
    connect(Teaching, &AbsTeachingTool::LineUpdatePos, this, [=](QPointF point){
        m_pCatBrushPixItem->DrawMove(1, m_yLastTeachingPoint, point);
        m_yLastTeachingPoint = point;
    });
    connect(Teaching, &AbsTeachingTool::LineEnd, this, [=](QPointF point){
        m_pCatBrushPixItem->DrawRelease(1, point);
        m_yLastTeachingPoint = point;
    });
    if(m_pCatGraphicsObject->GetDrawingBoardState() == CatGraphicsObject::PEN)
    {
        Teaching->SetState(AbsTeachingTool::TEAHINGTOOL_STATE_PEN);
    }
    if(m_pCatGraphicsObject->GetDrawingBoardState() == CatGraphicsObject::ERASER)
    {
        Teaching->SetState(AbsTeachingTool::TEAHINGTOOL_STATE_DORMANCY);
    }
}

void CatGraphicsScene::AddTeachingToolCompass()
{
    TeachingToolCompass *Teaching = new TeachingToolCompass;
    this->addItem(Teaching);
    m_pTeachingToolCompass.push_back(Teaching);
    if(m_pCatGraphicsObject->GetDrawingBoardState() == CatGraphicsObject::PEN
            || m_pCatGraphicsObject->GetDrawingBoardState() == CatGraphicsObject::ERASER)
    {
        Teaching->SetState(AbsTeachingTool::TEAHINGTOOL_STATE_DORMANCY);
    }
}

void CatGraphicsScene::Clear()
{
    this->clear();
    m_pTeachingToolCompass.clear();
    m_pTeachingToolProtractor.clear();
    m_pTeachingToolRuler.clear();
    m_pTeachingToolTrangle.clear();

    m_pCatBrushPixItem = nullptr;
    m_pCatBrushPixItem = new CatBrushPixItem();
    m_pCatBrushPixItem->SetBackgroundColor(Qt::transparent);
    m_pCatBrushPixItem->SetBrushSize(this->sceneRect());

    this->addItem(m_pCatBrushPixItem);
    switch (m_pCatGraphicsObject->GetDrawingBoardState()) {
        case CatGraphicsObject::PEN:
        {
            m_pCatBrushPixItem->SetMode(CatBrushObject::BrushMode::PenBrushMode);
            break;
        }
        case CatGraphicsObject::ERASER:
        {
            m_pCatBrushPixItem->SetMode(CatBrushObject::BrushMode::EraserMode);
            break;
        }
        default:
        {
            break;
        }
    }


}

void CatGraphicsScene::mousePressEventPenState(QPointF &point)
{
    m_bMousePress = true;
    switch (m_pCatGraphicsObject->GetDrawingBoardState()) {
        case CatGraphicsObject::PEN:
        case CatGraphicsObject::ERASER:
        {
            scenePress(1,point);
            update();
        }
        default:
        {
            break;
        }
    }
}

void CatGraphicsScene::mouseMoveEventPenState(QPointF &lastpoint, QPointF &point)
{
    if(m_bMousePress)
    {
        switch (m_pCatGraphicsObject->GetDrawingBoardState()) {
            case CatGraphicsObject::PEN:
            case CatGraphicsObject::ERASER:
            {
                sceneMove(1, lastpoint, point);
                update();
            }
            default:
            {
                break;
            }
        }
    }

}

void CatGraphicsScene::mouseReleaseEventPenState(QPointF &point)
{
    m_bMousePress = false;

    switch (m_pCatGraphicsObject->GetDrawingBoardState()) {
        case CatGraphicsObject::PEN:
        case CatGraphicsObject::ERASER:
        {
            sceneRelease(1, point);
            update();
        }
        default:
        {
            break;
        }
    }

}

void CatGraphicsScene::InitProperty()
{
    m_pCatGraphicsObject->SetDrawingBoardState(CatGraphicsObject::SELECT);

    m_pCatBrushPixItem = new CatBrushPixItem();
    m_pCatBrushPixItem->SetBackgroundColor(Qt::transparent);
    m_pCatBrushPixItem->SetBrushSize(this->sceneRect());
    this->addItem(m_pCatBrushPixItem);
    //QPixmapCache::setCacheLimit(204800);

    m_bMousePress = false;
}

void CatGraphicsScene::mousePressEventPenState(QGraphicsSceneMouseEvent *event)
{
    m_bMousePress = true;
    switch (m_pCatGraphicsObject->GetDrawingBoardState()) {
        case CatGraphicsObject::PEN:
        case CatGraphicsObject::ERASER:
        {
            scenePress(1,event->scenePos());
        }
        default:
        {
            break;
        }
    }
    if(m_pCatGraphicsObject->GetDrawingBoardState() == CatGraphicsObject::PEN)
    {
        View()->setCursor(QCursor(Qt::CrossCursor));
    }
    QGraphicsScene::mousePressEvent(event);
}

void CatGraphicsScene::mouseMoveEventPenState(QGraphicsSceneMouseEvent *event)
{
    if(m_bMousePress)
    {
        switch (m_pCatGraphicsObject->GetDrawingBoardState()) {
            case CatGraphicsObject::PEN:
            case CatGraphicsObject::ERASER:
            {
                sceneMove(1, event->lastScenePos(), event->scenePos());
            }
            default:
            {
                break;
            }
        }
        if(m_pCatGraphicsObject->GetDrawingBoardState() == CatGraphicsObject::PEN)
        {
            View()->setCursor(QCursor(Qt::CrossCursor));
        }
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void CatGraphicsScene::mouseReleaseEventPenState(QGraphicsSceneMouseEvent *event)
{
    m_bMousePress = false;

    switch (m_pCatGraphicsObject->GetDrawingBoardState()) {
        case CatGraphicsObject::PEN:
        case CatGraphicsObject::ERASER:
        {
            sceneRelease(1, event->scenePos());
        }
        default:
        {
            break;
        }
    }
    if(m_pCatGraphicsObject->GetDrawingBoardState() == CatGraphicsObject::PEN)
    {
        View()->setCursor(QCursor(Qt::ArrowCursor));
    }

    QGraphicsScene::mouseReleaseEvent(event);
}

bool CatGraphicsScene::event(QEvent *event)
{
    switch (event->type())
    {
        case QEvent::TouchEnd:
        case QEvent::TouchBegin:
        case QEvent::TouchUpdate:
        {
            if(touchEvent(static_cast<QTouchEvent*>(event)))
            {
                return true;
            }
            break;
        }
        default: break;
    }
    return QGraphicsScene::event(event);
}

void CatGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_bMousePress = true;
    QGraphicsScene::mousePressEvent(event);
    switch (m_pCatGraphicsObject->GetDrawingBoardState()) {
        case CatGraphicsObject::CAT_DRAWINGBOARD_STATE::PEN:
        case CatGraphicsObject::CAT_DRAWINGBOARD_STATE::ERASER:
        {
            mousePressEventPenState(event);
            break;
        }
        default: {
            break;
        }
    }
    //this->update();
}

void CatGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
    switch (m_pCatGraphicsObject->GetDrawingBoardState()) {
        case CatGraphicsObject::CAT_DRAWINGBOARD_STATE::PEN:
        case CatGraphicsObject::CAT_DRAWINGBOARD_STATE::ERASER:
        {
            mouseMoveEventPenState(event);
            break;
        }
        default: {
            break;
        }
    }
    //this->update();
}

void CatGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_bMousePress = false;
    QGraphicsScene::mouseReleaseEvent(event);
    switch (m_pCatGraphicsObject->GetDrawingBoardState()) {
        case CatGraphicsObject::CAT_DRAWINGBOARD_STATE::PEN:
        case CatGraphicsObject::CAT_DRAWINGBOARD_STATE::ERASER:
        {
            mouseReleaseEventPenState(event);
            break;
        }
        default: {
            break;
        }
    }
}

bool CatGraphicsScene::touchEvent(QTouchEvent *event)
{
    Q_UNUSED(event)
    bool rel = true;
    return rel;
}

bool CatGraphicsScene::scenePress(int id, const QPointF &pos)
{
    m_pCatBrushPixItem->DrawPress(id, pos);
    return true;
}

bool CatGraphicsScene::sceneMove(int id, const QPointF &presspos, const QPointF &pos)
{
    m_pCatBrushPixItem->DrawMove(id, presspos, pos);
    return true;
}

bool CatGraphicsScene::sceneRelease(int id, const QPointF &pos)
{
    m_pCatBrushPixItem->DrawRelease(id, pos);
    return true;
}

void CatGraphicsScene::On_DrawingBoard_SelectState()
{
    m_pCatGraphicsObject->SetDrawingBoardState(CatGraphicsObject::SELECT);
    foreach(auto temp, m_pTeachingToolCompass)
    {
        temp->SetState(AbsTeachingTool::TEAHINGTOOL_STATE_NONE);
    }
    foreach(auto temp, m_pTeachingToolProtractor)
    {
        temp->SetState(AbsTeachingTool::TEAHINGTOOL_STATE_NONE);
    }
    foreach(auto temp, m_pTeachingToolRuler)
    {
        temp->SetState(AbsTeachingTool::TEAHINGTOOL_STATE_NONE);
    }
    foreach(auto temp, m_pTeachingToolTrangle)
    {
        temp->SetState(AbsTeachingTool::TEAHINGTOOL_STATE_NONE);
    }
}

void CatGraphicsScene::On_DrawingBoard_PenState()
{
    m_pCatGraphicsObject->SetDrawingBoardState(CatGraphicsObject::PEN);
    m_pCatBrushPixItem->SetMode(CatBrushObject::BrushMode::PenBrushMode);
    foreach(auto temp, m_pTeachingToolCompass)
    {
        temp->SetState(AbsTeachingTool::TEAHINGTOOL_STATE_DORMANCY);
    }
    foreach(auto temp, m_pTeachingToolProtractor)
    {
        temp->SetState(AbsTeachingTool::TEAHINGTOOL_STATE_DORMANCY);
    }
    foreach(auto temp, m_pTeachingToolRuler)
    {
        temp->SetState(AbsTeachingTool::TEAHINGTOOL_STATE_PEN);
    }
    foreach(auto temp, m_pTeachingToolTrangle)
    {
        temp->SetState(AbsTeachingTool::TEAHINGTOOL_STATE_PEN);
    }
}

void CatGraphicsScene::On_DrawingBoard_EraserState()
{
    m_pCatGraphicsObject->SetDrawingBoardState(CatGraphicsObject::ERASER);
    m_pCatBrushPixItem->SetMode(CatBrushObject::BrushMode::EraserMode);
    foreach(auto temp, m_pTeachingToolCompass)
    {
        temp->SetState(AbsTeachingTool::TEAHINGTOOL_STATE_NONE);
    }
    foreach(auto temp, m_pTeachingToolProtractor)
    {
        temp->SetState(AbsTeachingTool::TEAHINGTOOL_STATE_NONE);
    }
    foreach(auto temp, m_pTeachingToolRuler)
    {
        temp->SetState(AbsTeachingTool::TEAHINGTOOL_STATE_NONE);
    }
    foreach(auto temp, m_pTeachingToolTrangle)
    {
        temp->SetState(AbsTeachingTool::TEAHINGTOOL_STATE_NONE);
    }
}
