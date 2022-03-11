#include "CatTableModel.h"
#include <QDebug>
#include <QDateTime>

bool Dtcomp_Time_Ascending(Model_Structure left, Model_Structure right)
{
    QDateTime timel = QDateTime::fromString(left.time, "yyyy-MM-dd HH:mm:ss");
    QDateTime timer = QDateTime::fromString(right.time, "yyyy-MM-dd HH:mm:ss");
    return timel < timer;
}

bool Dtcomp_Time_Descending(Model_Structure left, Model_Structure right)
{
    QDateTime timel = QDateTime::fromString(left.time, "yyyy-MM-dd HH:mm:ss");
    QDateTime timer = QDateTime::fromString(right.time, "yyyy-MM-dd HH:mm:ss");
    return timel > timer;
}

CatTableModel::CatTableModel(QObject *parent)
    : QStandardItemModel(parent)
{

}

CatTableModel::~CatTableModel()
{

}

void CatTableModel::AddData(Model_Structure data)
{
    QFont font("Ubuntu");
    font.setPixelSize(16);
    font.setWeight(QFont::Normal);
    QList<QStandardItem*> headitems;
    QStandardItem *item0 = new QStandardItem();
    item0->setData(data.check, Qt::UserRole);
    QStandardItem *item1 = new QStandardItem();
    item1->setForeground(QColor("#FFFFFF"));
    item1->setFont(font);
    item1->setData(data.id, Qt::UserRole);
    QStandardItem *item2 = new QStandardItem();
    item2->setForeground(QColor("#FFFFFF"));
    item2->setFont(font);
    item2->setData(data.state, Qt::UserRole);
    QStandardItem *item3 = new QStandardItem();
    item3->setForeground(QColor("#FFFFFF"));
    item3->setFont(font);
    item3->setData(data.time, Qt::UserRole);
    headitems.append(item0);
    headitems.append(item1);
    headitems.append(item2);
    headitems.append(item3);

    m_pCatTableViewTool->setRowHeight(rowCount(), 50);

    appendRow(headitems);
}

void CatTableModel::AddData(QList<Model_Structure> datas)
{
    foreach(auto data, datas)
    {
        QFont font("Ubuntu");
        font.setPixelSize(16);
        font.setWeight(QFont::Normal);
        QList<QStandardItem*> headitems;
        QStandardItem *item0 = new QStandardItem();
        item0->setData(data.check, Qt::UserRole);
        QStandardItem *item1 = new QStandardItem();
        item1->setForeground(QColor("#FFFFFF"));
        item1->setFont(font);
        item1->setData(data.id, Qt::UserRole);
        QStandardItem *item2 = new QStandardItem();
        item2->setForeground(QColor("#FFFFFF"));
        item2->setFont(font);
        item2->setData(data.state, Qt::UserRole);
        QStandardItem *item3 = new QStandardItem();
        item3->setForeground(QColor("#FFFFFF"));
        item3->setFont(font);
        item3->setData(data.time, Qt::UserRole);
        headitems.append(item0);
        headitems.append(item1);
        headitems.append(item2);
        headitems.append(item3);

        appendRow(headitems);

        m_pCatTableViewTool->setRowHeight(rowCount(), 50);

        //m_pCatTableViewTool->setRowHeight(rowCount(), 50);
    }
}

void CatTableModel::Clear()
{
    removeRows(1, rowCount() - 1);
}

void CatTableModel::SetCatTableViewTool(QTableView *view)
{
    m_pCatTableViewTool = view;
}


void CatTableModel::sort(int column, Qt::SortOrder order)
{
    if(column == 3)
    {
        QList<QDateTime> lists;
        m_yTableDatas.clear();
        for(int i = 1; i < rowCount(); i++)
        {
            qDebug() << item(i, column)->data(Qt::UserRole).toString();
            QDateTime time = QDateTime::fromString(item(i, column)->data(Qt::UserRole).toString(),
                                                   "yyyy-MM-dd HH:mm:ss");
            lists.append(time);
            Model_Structure data;
            data.check = item(i, 0)->data(Qt::UserRole).toInt();
            data.id = item(i, 1)->data(Qt::UserRole).toInt();
            data.state = item(i, 2)->data(Qt::UserRole).toBool();
            data.time = item(i, 3)->data(Qt::UserRole).toString();
            m_yTableDatas.append(data);
        }
        if(order == Qt::SortOrder::AscendingOrder)
        {
            qSort(m_yTableDatas.begin(), m_yTableDatas.end(), Dtcomp_Time_Ascending);
            Clear();
            AddData(m_yTableDatas);
        } else {
            qSort(m_yTableDatas.begin(), m_yTableDatas.end(), Dtcomp_Time_Descending);
            Clear();
            AddData(m_yTableDatas);
        }
    }
    QStandardItemModel::sort(column, order);
}
