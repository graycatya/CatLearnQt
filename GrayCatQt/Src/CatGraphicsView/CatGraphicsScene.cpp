#include "CatGraphicsScene.h"
#include "TeachingTools/TeachingToolCompass.h"
#include "TeachingTools/TeachingToolProtractor.h"
#include "TeachingTools/TeachingToolRuler.h"
#include "TeachingTools/TeachingToolTrangle.h"
#include "CatGraphicsView.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

CatGraphicsScene::CatGraphicsScene(QObject *parent)
    : QGraphicsScene(parent)
    , m_yView(nullptr)
{

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
}

void CatGraphicsScene::AddTeachingToolRuler()
{
    TeachingToolRuler *Teaching = new TeachingToolRuler;
    this->addItem(Teaching);
}

void CatGraphicsScene::AddTeachingToolTrangle()
{
    TeachingToolTrangle *Teaching = new TeachingToolTrangle;
    this->addItem(Teaching);
}

void CatGraphicsScene::AddTeachingToolCompass()
{
    TeachingToolCompass *Teaching = new TeachingToolCompass;
    this->addItem(Teaching);
}

void CatGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    QGraphicsScene::mousePressEvent(event);
}

void CatGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << event->pos();
    QGraphicsScene::mouseMoveEvent(event);
}

void CatGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    QGraphicsScene::mouseReleaseEvent(event);
}
