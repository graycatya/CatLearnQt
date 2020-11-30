#include "CatGraphicsView.h"
#include <QDebug>

CatGraphicsView::CatGraphicsView(QWidget *parent)
    : QGraphicsView(parent)
{
    InitProperty();
}

CatGraphicsView::~CatGraphicsView()
{

}

void CatGraphicsView::ScaleZoomIn()
{

    scale(1.2, 1.2);
}

void CatGraphicsView::ScaleZoomOut()
{

    scale(1 / 1.2, 1 / 1.2);
}

void CatGraphicsView::Reset()
{
    this->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    QMatrix q;
    q.setMatrix(1, matrix().m12(), matrix().m21(),1, matrix().dx(), matrix().dy());
    setMatrix(q,false);
}

void CatGraphicsView::InitProperty()
{
    scale(1.0 , 1.0);
}
