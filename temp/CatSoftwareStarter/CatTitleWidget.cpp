#include "CatTitleWidget.h"
#include <QMouseEvent>

CatTitleWidget::CatTitleWidget(QWidget *parent)
    : QLabel(parent)
{

}

CatTitleWidget::~CatTitleWidget()
{

}

void CatTitleWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        emit doubleClick();
    }
}
