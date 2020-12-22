#include "CatQcLineChart.h"

CatQcLineChart::CatQcLineChart(QWidget *parent)
    : CatQcustomplot(parent)
    , m_bTracer(false)
    , m_pTracer(new QCPItemTracer(this))
    , m_pTracerXText(new QCPItemText(this))
    , m_pTracerYText(new QCPItemText(this))
{
    InitUi();
    InitProperty();
}

CatQcLineChart::~CatQcLineChart()
{

}

void CatQcLineChart::SetTracer(bool tracer)
{
    m_bTracer = tracer;
    m_pTracer->setVisible(m_bTracer);
    m_pTracerXText->setVisible(m_bTracer);
    m_pTracerYText->setVisible(m_bTracer);
}

void CatQcLineChart::SetSelectTraceGraph(QCPGraph *graph)
{
    m_pTraceGraph = graph;
}

void CatQcLineChart::InitUi()
{
    m_pTracer->setVisible(false);
    m_pTracer->setInterpolating(false);
    m_pTracerXText->setVisible(false);
    m_pTracerYText->setVisible(false);
}

void CatQcLineChart::InitProperty()
{

}

void CatQcLineChart::mouseMoveEvent(QMouseEvent *event)
{
    QCustomPlot::mouseMoveEvent(event);
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
        }

    }
}

void CatQcLineChart::showEvent(QShowEvent *event)
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

void CatQcLineChart::SetTracerPen(QPen pen)
{
    m_pTracer->setPen(pen);
}

void CatQcLineChart::SetTracerPenWidth(int width)
{
    QPen pen = m_pTracer->pen();
    pen.setWidth(width);
    m_pTracer->setPen(pen);
}

void CatQcLineChart::SetTracerPenColor(QColor color)
{
    QPen pen = m_pTracer->pen();
    pen.setColor(color);
    m_pTracer->setPen(pen);
}

void CatQcLineChart::SetTracerXTextPen(QPen pen)
{
    m_pTracerXText->setPen(pen);
}

void CatQcLineChart::SetTracerXTextPenWidth(int width)
{
    QPen pen = m_pTracerXText->pen();
    pen.setWidth(width);
    m_pTracerXText->setPen(pen);
}

void CatQcLineChart::SetTracerXTextPenColor(QColor color)
{
    QPen pen = m_pTracerXText->pen();
    pen.setColor(color);
    m_pTracerXText->setPen(pen);
}

void CatQcLineChart::SetTracerXTextColor(QColor color)
{
    m_pTracerXText->setColor(color);
}

void CatQcLineChart::SetTracerXTextBackgroundColor(QColor color)
{
    m_pTracerXText->setBackgroundColor(color);
}

void CatQcLineChart::SetTracerYTextPen(QPen pen)
{
    m_pTracerYText->setPen(pen);
}

void CatQcLineChart::SetTracerYTextPenWidth(int width)
{
    QPen pen = m_pTracerYText->pen();
    pen.setWidth(width);
    m_pTracerYText->setPen(pen);
}

void CatQcLineChart::SetTracerYTextPenColor(QColor color)
{
    QPen pen = m_pTracerYText->pen();
    pen.setColor(color);
    m_pTracerYText->setPen(pen);
}

void CatQcLineChart::SetTracerYTextColor(QColor color)
{
    m_pTracerYText->setColor(color);
}

void CatQcLineChart::SetTracerYTextBackgroundColor(QColor color)
{
    m_pTracerYText->setBackgroundColor(color);
}
