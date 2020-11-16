#include "ProcessObject.h"

ProcessObject::ProcessObject(QObject *parent)
    : QObject(parent)
    , m_qstate(STATE::SELECT)
    , MinWidth(100)
    , MinHeight(100)
    , MaxWidth(9999)
    , MaxHeight(9999)
    , MaxParentWidth(9999)
    , MaxParentHeight(9999)
    , m_qStartPos(QPoint(-1, -1))
    , m_qEndPos(m_qStartPos)
    , m_qLeftTopPos(m_qStartPos)
    , m_qRightBottomPos(m_qStartPos)
    , m_qRightTopPos(m_qStartPos)
    , m_qLeftBottomPos(m_qStartPos)
{

}

ProcessObject::~ProcessObject()
{

}

void ProcessObject::SetGeometry(int x, int y, int width, int height)
{
    int my_width = MinWidth, my_height = MinHeight;
    my_width = qMax(width, MinWidth);
    my_width = qMin(my_width, MaxWidth);
    my_height = qMax(height, MinHeight);
    my_height = qMin(my_height, MaxHeight);
    m_qLeftTopPos = QPoint(x,y);
    m_qLeftBottomPos = QPoint(x, y + my_height);

    m_qRightTopPos = QPoint(x + my_width, y);
    m_qRightBottomPos = QPoint(x + my_width, y + my_height);
    ComparePoint(m_qLeftTopPos, m_qRightBottomPos);
}

void ProcessObject::SetMinWidth(int width)
{
    MinWidth = width;
}

int ProcessObject::GetMinWidth() const
{
    return MinWidth;
}

void ProcessObject::SetMinHeight(int height)
{
    MinHeight = height;
}

int ProcessObject::GetMinHeight() const
{
    return MinHeight;
}

void ProcessObject::SetMinSize(QSize size)
{
    MinWidth = size.width();
    MinHeight = size.height();
}

QSize ProcessObject::GetMinSize() const
{
    return QSize(MinWidth, MinHeight);
}

void ProcessObject::SetMaxWidth(int width)
{
    MaxWidth = width;
}

int ProcessObject::GetMaxWidth() const
{
    return MaxWidth;
}

void ProcessObject::SetMaxHeight(int height)
{
    MaxHeight = height;
}

int ProcessObject::GetMaxHeight() const
{
    return MaxHeight;
}

void ProcessObject::SetMaxSize(QSize size)
{
    MaxWidth = size.width();
    MaxHeight = size.height();
}

QSize ProcessObject::GetMaxSize() const
{
    return QSize(MaxWidth, MaxHeight);
}

void ProcessObject::SetMaxParentSize(QSize maxparentsize)
{
   MaxParentWidth = maxparentsize.width();
   MaxParentHeight = maxparentsize.height();
}

QSize ProcessObject::GetMaxParentSize() const
{
    return QSize(MaxParentWidth, MaxParentHeight);
}

int ProcessObject::GetMaxParentWidget() const
{
    return MaxParentWidth;
}

int ProcessObject::GetMaxParentHeight() const
{
    return MaxParentHeight;
}

int ProcessObject::x() const
{
    return m_qLeftTopPos.x();
}

int ProcessObject::y() const
{
    return m_qLeftTopPos.y();
}

int ProcessObject::width() const
{
    int width = m_qRightBottomPos.x() - m_qLeftTopPos.x();
    return width;
}

int ProcessObject::height() const
{
    int height = m_qRightBottomPos.y() - m_qLeftTopPos.y();
    return height;
}

bool ProcessObject::IsInArea(QPoint pos)
{
    if(pos.x() > m_qLeftTopPos.x()
            && pos.x() < m_qRightBottomPos.x()
            && pos.y() > m_qLeftTopPos.y()
            && pos.y() < m_qRightBottomPos.y())
    {
        return true;
    }
    return false;
}

void ProcessObject::Move(QPoint pos)
{
    int m_ywidth = width();
    int m_yheight = height();

    int x = m_qLeftTopPos.x() + pos.x();
    int y = m_qLeftTopPos.y() + pos.y();

    if(x < 0)
    {
        x = 0;
    } else if(x + m_ywidth > MaxParentWidth)
    {
        x = MaxParentWidth - m_ywidth;
    }

    if(y < 0)
    {
        y = 0;
    } else if(y + m_yheight > MaxParentHeight)
    {
        y = MaxParentHeight - m_yheight;
    }

    m_qStartPos = QPoint(x, y);
    m_qEndPos = QPoint(x + m_ywidth, y + m_yheight);
    m_qLeftTopPos = m_qStartPos;
    m_qRightBottomPos = m_qEndPos;
}

void ProcessObject::SetState(ProcessObject::STATE state)
{
    m_qstate = state;
}

ProcessObject::STATE ProcessObject::GetState() const
{
    return m_qstate;
}

void ProcessObject::SetStart(QPoint pos)
{
    m_qStartPos = pos;
}

QPoint ProcessObject::GetStart() const
{
    return m_qStartPos;
}

void ProcessObject::SetEnd(QPoint pos)
{
    m_qEndPos = pos;
    m_qLeftTopPos = m_qStartPos;
    m_qRightBottomPos = m_qEndPos;
    ComparePoint(m_qLeftTopPos, m_qRightBottomPos);
}

QPoint ProcessObject::GetEnd() const
{
    return m_qEndPos;
}

QPoint ProcessObject::GetLeftTopPos() const
{
    return m_qLeftTopPos;
}

QPoint ProcessObject::GetRightBottomPos() const
{
    return m_qRightBottomPos;
}

void ProcessObject::ComparePoint(QPoint &leftTop, QPoint &rightBottom)
{
    QPoint lefttop = leftTop;
    QPoint rightbottom = rightBottom;

    if(lefttop.x() <= rightbottom.x()) {
        // 判断end 在start右上的情况
        if(!(lefttop.y() <= rightBottom.y()))
        {
            leftTop.setY(rightbottom.y());
            rightBottom.setY(lefttop.y());
        }
        // end 在start右下的情况 不用判断
    } else {
        // 判断end 在start左下的情况
        if(lefttop.y() < rightbottom.y()) {
            leftTop.setX(rightbottom.x());
            rightBottom.setX(lefttop.x());
        } else { // 判断end 在start左上的情况
            QPoint temp;
            temp = leftTop;
            leftTop = rightBottom;
            rightBottom = temp;
        }
    }
    //m_qStartPos = leftTop;
    //m_qEndPos = rightBottom;
}
