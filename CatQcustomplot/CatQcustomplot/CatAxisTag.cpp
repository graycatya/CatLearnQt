#include "CatAxisTag.h"

CatAxisTag::CatAxisTag(QCPAxis *parent)
    : QObject(parent)
    , m_pAxis(parent)
{
    InitUi();
    InitProperty();
}

CatAxisTag::~CatAxisTag()
{

}

void CatAxisTag::UpdatePosition(double value)
{
    /*
     * 因为箭头和文本标签都链接到虚拟跟踪器(通过锚)更新虚拟跟踪器坐标就足够了。
     * 的水平坐标类型被设置为ptAxisRectRatio，以保持它在右侧对齐
     * 对于rect轴，它总是保持为1。垂直坐标类型被设置为
     * 父轴的ptPlotCoordinates，因此垂直坐标被设置为new值。
    */
    mDummyTracer->position->setCoords(1, value);
    /*
     * 我们想要箭头和轴的骨干在同一水平位置，
     * 即使轴有一定的偏移从轴rect边界(如增加的第二个y轴)。
     * 因此我们设置箭头末端(头部)的水平像素位置到轴的偏移量(像素到矩形轴边界的距离)。
     * 这是因为箭头末端的父锚是虚拟跟踪器，如前所述，绑定到右轴rect边界。
    */
    mArrow->end->setCoords(m_pAxis->offset(), 0);
}

void CatAxisTag::InitUi()
{
    mDummyTracer = new QCPItemTracer(m_pAxis->parentPlot());
    mDummyTracer->setVisible(false);
    mDummyTracer->position->setTypeX(QCPItemPosition::ptAxisRectRatio);
    mDummyTracer->position->setTypeY(QCPItemPosition::ptPlotCoords);
    mDummyTracer->position->setAxes(0, m_pAxis);
    mDummyTracer->position->setCoords(1, 0);

    mArrow = new QCPItemLine(m_pAxis->parentPlot());
    mArrow->setLayer("overlay");
    mArrow->setClipToAxisRect(false);
    mArrow->setHead(QCPLineEnding::esSpikeArrow);
    mArrow->end->setParentAnchor(mArrow->end);
    mArrow->start->setParentAnchor(mArrow->end);
    mArrow->start->setCoords(15, 0);

    mLabel = new QCPItemText(m_pAxis->parentPlot());
    mLabel->setLayer("overlay");
    mLabel->setClipToAxisRect(false);
    mLabel->setPadding(QMargins(3, 0, 3, 0));
    mLabel->setBrush(QBrush(Qt::white));
    mLabel->setPen(QPen(Qt::blue));
    mLabel->setPositionAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    mLabel->position->setParentAnchor(mArrow->start);
}

void CatAxisTag::InitProperty()
{
    if(mDummyTracer)
        mDummyTracer->parentPlot()->removeItem(mDummyTracer);
    if(mArrow)
        mArrow->parentPlot()->removeItem(mArrow);
    if(mLabel)
        mLabel->parentPlot()->removeItem(mLabel);
}

void CatAxisTag::SetPen(const QPen &pen)
{
    mArrow->setPen(pen);
    mLabel->setPen(pen);
}

void CatAxisTag::SetLabelBrush(const QBrush &brush)
{
    mLabel->setBrush(brush);
}

void CatAxisTag::SetLabelText(const QString &text)
{
    mLabel->setText(text);
}
