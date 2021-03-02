#include "CatCustomChart.h"

CatCustomChart::CatCustomChart(QWidget *parent)
    : CatQcustomplot(parent)
    , m_bTracer(false)
    , m_pTracer(new QCPItemTracer(this))
    , m_pTracerXText(new QCPItemText(this))
    , m_pTracerYText(new QCPItemText(this))
{
    InitUi();
    InitProperty();
}

CatCustomChart::~CatCustomChart()
{

}

void CatCustomChart::SetTracer(bool tracer)
{
    m_bTracer = tracer;
    m_pTracer->setVisible(m_bTracer);
    m_pTracerXText->setVisible(m_bTracer);
    m_pTracerYText->setVisible(m_bTracer);
}

void CatCustomChart::SetSelectTraceGraph(QCPGraph *graph)
{
    m_pTraceGraph = graph;
}

void CatCustomChart::InitUi()
{
    QFont font;
    font.setFamily("Ubuntu");
    font.setPixelSize(11);
    m_pTracer->setVisible(false);
    m_pTracer->setInterpolating(false);
    m_pTracerXText->setVisible(false);
    m_pTracerXText->setPositionAlignment(Qt::AlignBottom | Qt::AlignRight);

    m_pTracerXText->position->setCoords(0, 0.99);
    m_pTracerXText->position->setParentAnchorX(m_pTracer->position);
    m_pTracerXText->setText("---");
    m_pTracerXText->setPadding(QMargins(5,5,5,5));
    m_pTracerYText->setVisible(false);
    m_pTracerYText->setPositionAlignment(Qt::AlignTop|Qt::AlignLeft);

    m_pTracerYText->position->setCoords(0.01, 0);
    m_pTracerYText->position->setParentAnchorY(m_pTracer->position);
    m_pTracerYText->setText("---");
    m_pTracerYText->setPadding(QMargins(5,5,5,5));

}

void CatCustomChart::InitProperty()
{
    setMouseTracking(true);
}

void CatCustomChart::mouseMoveEvent(QMouseEvent *event)
{
    CatQcustomplot::mouseMoveEvent(event);
    if(m_bTracer)
    {
        if(getGraphs().contains(m_pTraceGraph) && m_pTraceGraph->data().data()->size() != 0)
        {

            //像素坐标转plot坐标
            double x = xAxis->pixelToCoord(event->pos().x());
            m_pTracer->setGraph(m_pTraceGraph);
            m_pTracer->setGraphKey(x);
            double traceX = m_pTracer->position->key();
            double traceY = m_pTracer->position->value();


            //游标文本框
            m_pTracerXText->setText(QDateTime::fromMSecsSinceEpoch(traceX * 1000.0).toString("MM-dd hh:mm:ss"));
            m_pTracerYText->setText(QString::number(traceY));
        

            /*
            //计算游标X值对应的所有曲线的Y值
            for(int i = 0; i < graphCount(); i++)
            {
                //搜索左边离traceX最近的key对应的点，详情参考findBegin函数的帮助 true代表向左搜索
                QCPDataContainer<QCPGraphData>::const_iterator coorPoint = graph(i)->data().data()->findBegin(traceX, true);
                qDebug() << QString("graph%1对应的Y值是").arg(i) << coorPoint->value;

            }
            */
            replot();
        }

    }
}

void CatCustomChart::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
    if(graphCount() > 0)
    {
        m_pTraceGraph = graph(0);
        m_bTracer = true;
    } else {
        m_pTraceGraph = nullptr;
        m_bTracer = false;
    }
}

void CatCustomChart::SetTracerPen(QPen pen)
{
    m_pTracer->setPen(pen);
    replot();
}

void CatCustomChart::SetTracerPenStyle(Qt::PenStyle style)
{
    QPen pen = m_pTracer->pen();
    pen.setStyle(style);
    m_pTracer->setPen(pen);
    replot();
}

void CatCustomChart::SetTracerPenWidth(int width)
{
    QPen pen = m_pTracer->pen();
    pen.setWidth(width);
    m_pTracer->setPen(pen);
    replot();
}

void CatCustomChart::SetTracerPenColor(QColor color)
{
    QPen pen = m_pTracer->pen();
    pen.setColor(color);
    m_pTracer->setPen(pen);
    replot();
}

void CatCustomChart::SetTracerStyle(QCPItemTracer::TracerStyle style)
{
    m_pTracer->setStyle(style);
    replot();
}

void CatCustomChart::SetTracerXTextPen(QPen pen)
{
    m_pTracerXText->setPen(pen);
    replot();
}

void CatCustomChart::SetTracerXTextPenWidth(int width)
{
    QPen pen = m_pTracerXText->pen();
    pen.setWidth(width);
    m_pTracerXText->setPen(pen);
    replot();
}

void CatCustomChart::SetTracerXTextPenColor(QColor color)
{
    QPen pen = m_pTracerXText->pen();
    pen.setColor(color);
    m_pTracerXText->setPen(pen);
    replot();
}

void CatCustomChart::SetTracerXTextColor(QColor color)
{
    m_pTracerXText->setColor(color);
    replot();
}

void CatCustomChart::SetTracerXTextBackgroundColor(QColor color)
{
    m_pTracerXText->setBackgroundColor(color);
    replot();
}

void CatCustomChart::SetTracerXPositionType(QCPItemPosition::PositionType type)
{
    m_pTracerXText->position->setType(type);
    switch (type) {
    case QCPItemPosition::ptViewportRatio: {
        m_pTracerYText->position->setCoords(0.0, 0.5);
        break;
    }
    case QCPItemPosition::ptAxisRectRatio: {
        m_pTracerXText->position->setCoords(0, 0.99);
        break;
    }
    default:
        m_pTracerYText->position->setCoords(0, 0);
        break;
    }
    m_pTracerXText->position->setParentAnchorX(m_pTracer->position);
    replot();
}

void CatCustomChart::SetTracerYTextPen(QPen pen)
{
    m_pTracerYText->setPen(pen);
    replot();
}

void CatCustomChart::SetTracerYTextPenWidth(int width)
{
    QPen pen = m_pTracerYText->pen();
    pen.setWidth(width);
    m_pTracerYText->setPen(pen);
    replot();
}

void CatCustomChart::SetTracerYTextPenColor(QColor color)
{
    QPen pen = m_pTracerYText->pen();
    pen.setColor(color);
    m_pTracerYText->setPen(pen);
    replot();
}

void CatCustomChart::SetTracerYTextColor(QColor color)
{
    m_pTracerYText->setColor(color);
    replot();
}

void CatCustomChart::SetTracerYTextBackgroundColor(QColor color)
{
    m_pTracerYText->setBackgroundColor(color);
    replot();
}

void CatCustomChart::SetTracerYPositionType(QCPItemPosition::PositionType type)
{
    m_pTracerYText->position->setType(type);
    switch (type) {
    case QCPItemPosition::ptViewportRatio: {
        m_pTracerYText->position->setCoords(0.5, 0);
        break;
    }
    case QCPItemPosition::ptAxisRectRatio: {
        m_pTracerYText->position->setCoords(0.01, 0);
        break;
    }
    default:
        m_pTracerYText->position->setCoords(0, 0);
        break;
    }
    m_pTracerYText->position->setParentAnchorY(m_pTracer->position);
    replot();
}
