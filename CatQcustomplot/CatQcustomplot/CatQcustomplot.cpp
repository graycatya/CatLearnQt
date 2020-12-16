#include "CatQcustomplot.h"

CatQcustomplot::CatQcustomplot(QWidget *parent)
    : QCustomPlot(parent)
{

}

CatQcustomplot::~CatQcustomplot()
{

}

QBrush CatQcustomplot::GetBackground()
{
    return background();
}

QBrush CatQcustomplot::GetLegendBackground()
{
    return legend->brush();
}

QStringList CatQcustomplot::ScatterShapeList()
{
    QStringList list;
    list.clear();
    /*QMetaEnum metaEnum = QMetaEnum::fromType<QCPScatterStyle::ScatterShape>();
    for (int i = 0; i < metaEnum.keyCount(); i++) {
        list += metaEnum.valueToKey(metaEnum.value(i));
    }*/
    return list;
}

void CatQcustomplot::SetBackground(QBrush brush)
{
    setBackground(brush);
}

void CatQcustomplot::SetLegendBackground(QBrush brush)
{
    legend->setBrush(brush);
}
