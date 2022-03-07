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
    qDebug() << column << " : " << order;
}
