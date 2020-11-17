#include "RimlessWindowBase.h"
#include <QGraphicsDropShadowEffect>


RimlessWindowBase::RimlessWindowBase(QWidget *parent)
    : QWidget(parent)
    , m_pScreen(nullptr)
{
    InitProperty();
}

RimlessWindowBase::~RimlessWindowBase()
{

}

void RimlessWindowBase::InitProperty()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    setAutoFillBackground(true);

}

bool RimlessWindowBase::ZoomIsInArea(QRect rect, QPoint pos)
{
    if(pos.x() > rect.x()
            && pos.x() < rect.x() + rect.width()
            && pos.y() > rect.y()
            && pos.y() < rect.y() + rect.height())
    {
        return true;
    }
    return false;
}
