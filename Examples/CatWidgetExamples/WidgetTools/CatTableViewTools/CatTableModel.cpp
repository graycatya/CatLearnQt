#include "CatTableModel.h"
#include <QDebug>

CatTableModel::CatTableModel(QObject *parent)
    : QStandardItemModel(parent)
{

}

CatTableModel::~CatTableModel()
{

}

void CatTableModel::sort(int column, Qt::SortOrder order)
{
    //qDebug() << column << " : " << order;
    if(column == 3)
    {
        for(int i = 1; i < rowCount(); i++)
        {
            qDebug() << item(i, column)->data(Qt::UserRole).toString();
        }
    }
    QStandardItemModel::sort(column, order);
}
