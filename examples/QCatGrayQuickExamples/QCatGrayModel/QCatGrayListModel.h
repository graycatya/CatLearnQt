#ifndef QCATGRAYLISTMODEL_H
#define QCATGRAYLISTMODEL_H

#include <QAbstractListModel>

template <typename T>
class QCatGrayListModel : public QAbstractListModel
{

public:
    // 声明父类
    using Parent = QAbstractListModel;

    explicit QCatGrayListModel(QObject* parent = nullptr);
    QCatGrayListModel(const QList<T>& nodeList, QObject* parent = nullptr);

    const QList<T>& nodeList() const
    {
        return m_nodeList;
    }

    // 设置节点链表
    void setNodeList(const QList<T>& nodeList);

    int rowCount(const QModelIndex& parent) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;

    bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex());

    Qt::ItemFlags flags(const QModelIndex& index)const override;
    Qt::DropActions supportedDropActions() const override;

protected:
    QList<T> m_nodeList;

};

#endif
