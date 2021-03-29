#include "AbsDrawingBoardBase.h"

AbsDrawingBoardBase::AbsDrawingBoardBase(QObject *parent)
    : QObject(parent)
{
    InitProperty();
}

AbsDrawingBoardBase::~AbsDrawingBoardBase()
{

}

void AbsDrawingBoardBase::InitProperty()
{
    m_ySize = QRectF(0, 0, 0, 0);
    m_yPadding = 0;
}
