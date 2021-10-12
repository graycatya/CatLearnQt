#ifndef CATTREEMODEL_H
#define CATTREEMODEL_H

#include "CatListModel.h"
#include <QJsonObject>



const static QString ModelDepthKey = QStringLiteral("TreeModel_depth");
const static QString ModelExpendKey = QStringLiteral("TreeModel_expend");
const static QString ModelChildrenExpendKey = QStringLiteral("TreeModel_childrenExpend");
const static QString ModelHasChildrendKey = QStringLiteral("TreeModel_hasChildren");
const static QString ModelParentKey = QStringLiteral("TreeModel_parent");
const static QString ModelChildrenKey = QStringLiteral("TreeModel_children");

const static QString ModelRecursionKey = QStringLiteral("subType");
const static QStringList ModelFilterKeyList = { ModelDepthKey, ModelExpendKey,
                                              ModelChildrenExpendKey, ModelHasChildrendKey,
                                              ModelParentKey, ModelChildrenKey };

class CatTreeModel : public CatListModel<QJsonObject>
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
public:
    // 声明父类
    using Parent = CatListModel<QJsonObject>;

    CatTreeModel() {}
    ~CatTreeModel() {}
    // 从json文件读入数据
    Q_INVOKABLE void loadFromJson(const QString& jsonPath, const QString& recursionKey = ModelRecursionKey);
    // 导出到json文件
    Q_INVOKABLE bool saveToJson(const QString& jsonPath, bool compact = false) const;
    Q_INVOKABLE void clear();
    // 设置指定节点的数值
    Q_INVOKABLE void setNodeValue(int index, const QString& key, const QVariant& value);
    // 在index添加子节点。刷新父级，返回新项index
    Q_INVOKABLE int addNode(int index, const QJsonObject& json);
    Q_INVOKABLE int addNode(const QModelIndex& index, const QJsonObject& json)
    {
        return addNode(index.row(), json);
    }

    // 删除。递归删除所有子级，刷新父级
    Q_INVOKABLE void remove(int index);
    Q_INVOKABLE void remove(const QModelIndex& index)
    {
        remove(index.row());
    }
    Q_INVOKABLE QList<int> search(const QString& key, const QString& value, Qt::CaseSensitivity cs = Qt::CaseInsensitive) const;
    // 展开子级。只展开一级，不递归
    Q_INVOKABLE void expand(int index);
    Q_INVOKABLE void expand(const QModelIndex& index)
    {
        expand(index.row());
    }

    // 折叠子级。递归全部子级。
    Q_INVOKABLE void collapse(int index);
    Q_INVOKABLE void collapse(const QModelIndex& index)
    {
        collapse(index.row());
    }

    // 展开到指定项。递归
    Q_INVOKABLE void expandTo(int index);
    Q_INVOKABLE void expandTo(const QModelIndex& index)
    {
        expandTo(index.row());
    }

    // 展开全部
    Q_INVOKABLE void expandAll();

    // 折叠全部
    Q_INVOKABLE void collapseAll();

    int count() const;

    Q_INVOKABLE QVariant data(int idx, int role = Qt::DisplayRole) const;


signals:
    void countChanged();
    void showMessage(QString message) const;

protected:
    void gen(int depth, const QJsonArray& dataArray);
    QJsonArray getChildren(int parentIndex, int parentDepth) const;
    int addWithoutDepth(const QJsonObject& json);
    void innerUpdate(int index);

private:
    QString m_recursionKey = ModelRecursionKey;
};




#endif // CATTREEMODEL_H
