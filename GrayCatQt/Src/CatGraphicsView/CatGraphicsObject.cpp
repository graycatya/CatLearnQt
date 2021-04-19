#include "CatGraphicsObject.h"

CatGraphicsObject::CatGraphicsObject(QObject *parent)
    : QObject(parent)
{
    m_yDrawingState = NO_STATE;
    m_yLastDrawingState = NO_STATE;
}

CatGraphicsObject::~CatGraphicsObject()
{

}
