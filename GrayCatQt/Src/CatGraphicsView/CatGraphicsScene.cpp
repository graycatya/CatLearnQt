#include "CatGraphicsScene.h"
#include "TeachingTools/TeachingToolCompass.h"
#include "TeachingTools/TeachingToolProtractor.h"
#include "TeachingTools/TeachingToolRuler.h"
#include "TeachingTools/TeachingToolTrangle.h"
#include "CatGraphicsView.h"

#include "DrawingBoardTools/CatGraphicPen.h"

#include <QGraphicsSceneMouseEvent>
#include <QDebug>


CatGraphicsScene::CatGraphicsScene(QObject *parent)
    : QGraphicsScene(parent)
    , m_yView(nullptr)
    , m_pCatGraphicsObject(new CatGraphicsObject(this))
{
    InitProperty();
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
    this->addItem(Teaching);
    m_pTeachingToolRuler.push_back(Teaching);
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
    m_pTeachingToolTrangle.push_back(Teaching);
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

void CatGraphicsScene::InitProperty()
{
    m_pCatGraphicsObject->SetDrawingBoardState(CatGraphicsObject::SELECT);
    m_pCurrentCatGraphicPen = nullptr;
    m_bMousePress = false;
}

void CatGraphicsScene::mousePressEventPenState(QGraphicsSceneMouseEvent *event)
{
    CatGraphicPen *pen = new CatGraphicPen;
    this->addItem(pen);
    qDebug() << "s: " << event->screenPos() << " : " << event->scenePos();
    pen->GraphicPenAddPoint(event->scenePos());
    m_pCurrentCatGraphicPen = pen;
}

void CatGraphicsScene::mouseMoveEventPenState(QGraphicsSceneMouseEvent *event)
{
    if(m_bMousePress)
    {
        qDebug() << "s: " << event->screenPos() << " : " << event->scenePos();
        m_pCurrentCatGraphicPen->GraphicPenAddPoint(event->scenePos());
    }
}

void CatGraphicsScene::mouseReleaseEventPenState(QGraphicsSceneMouseEvent *event)
{
    m_pCurrentCatGraphicPen  = nullptr;
}

void CatGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_bMousePress = true;
    QGraphicsScene::mousePressEvent(event);
    switch (m_pCatGraphicsObject->GetDrawingBoardState()) {
        case CatGraphicsObject::CAT_DRAWINGBOARD_STATE::PEN: {
            mousePressEventPenState(event);
            break;
        }
        default: {
            break;
        }
    }
    this->update();
}

void CatGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
    switch (m_pCatGraphicsObject->GetDrawingBoardState()) {
        case CatGraphicsObject::CAT_DRAWINGBOARD_STATE::PEN: {
            mouseMoveEventPenState(event);
            break;
        }
        default: {
            break;
        }
    }
    this->update();
}

void CatGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_bMousePress = false;
    QGraphicsScene::mouseReleaseEvent(event);
    switch (m_pCatGraphicsObject->GetDrawingBoardState()) {
        case CatGraphicsObject::CAT_DRAWINGBOARD_STATE::PEN: {
            mouseReleaseEventPenState(event);
            break;
        }
        default: {
            break;
        }
    }
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
