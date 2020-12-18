#include "CatLineChart.h"

CatLineChart::CatLineChart(QWidget *parent)
    : CatQcustomplot(parent)
    , m_pSelectGraph(nullptr)
{
    InitUi();
    InitProperty();
    InitConnect();
}

CatLineChart::~CatLineChart()
{

}

void CatLineChart::InitUi()
{

}

void CatLineChart::InitProperty()
{
    //添加自定义类控制
    setAttribute(Qt::WA_StyledBackground,true);
}

void CatLineChart::InitConnect()
{
    /*
     *  用户更改QCustomPlot中的选择后(例如通过单击),将发出此信号。
     *  该方法用来做图列与曲线的双向选择绑定
    */
    connect(this, &QCustomPlot::selectionChangedByUser, this, [=](){
        for(auto graph : this->mGraphs)
        {
            QCPPlottableLegendItem *item = legend->itemWithPlottable(graph);
            if(item->selected() || graph->selected())
            {
                graph->selectionDecorator()->setPen(m_pSelectionGraphPen);
                item->setSelected(true);
                graph->setSelection(QCPDataSelection(graph->data()->dataRange()));
            }
        }
    });
}
