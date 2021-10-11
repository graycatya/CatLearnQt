#include "CatTreeModel.h"
#include "ModelTools.h"
#include <QJsonArray>

#include <QDebug>

namespace CatModel {

void CatModel::CatTreeModel::loadFromJson(const QString &jsonPath, const QString &recursionKey)
{
    QJsonArray arr;
    if(!readJsonFile(jsonPath, arr))
    {
        return;
    }
    m_recursionKey = recursionKey;
    beginResetModel();
    m_nodeList.clear();
    gen(0, arr);
    endResetModel();
    countChanged();
}

bool CatModel::CatTreeModel::saveToJson(const QString &jsonPath, bool compact) const
{
    QJsonArray arr;
    int depth = 0;
    for(int i = 0; i < m_nodeList.size(); ++i)
    {
        depth = m_nodeList.at(i).value(ModelDepthKey).toInt();
        if(depth == 0)
        {
            auto node = QJsonObject(m_nodeList.at(i));
            for(auto k : ModelFilterKeyList)
            {
                node.remove(k);
            }
            auto children = getChildren(i, depth);
            if(!children.isEmpty())
            {
                node[m_recursionKey] = children;
            }
            arr.push_back(node);
        }
    }
    return writeJsonFile(jsonPath, arr, compact);
}

void CatModel::CatTreeModel::clear()
{
    beginResetModel();
    m_nodeList.clear();
    endResetModel();
    countChanged();
}

void CatModel::CatTreeModel::setNodeValue(int index, const QString &key, const QVariant &value)
{
    if(index < 0 || index >= m_nodeList.size())
    {
        return;
    }
    if(m_nodeList.at(index).value(key).toVariant() != value)
    {
        m_nodeList[index][key] = QJsonValue::fromVariant(value);
        emit dataChanged(Parent::index(index), Parent::index(index), { Qt::DisplayRole, Qt::EditRole });
    }
}

int CatModel::CatTreeModel::addNode(int index, const QJsonObject &json)
{
    if(index < 0 || index >= m_nodeList.size())
    {
        return addWithoutDepth(json);
    }
    int depth = m_nodeList.at(index).value(ModelDepthKey).toInt();
    int i = index + 1;
    for(; i < m_nodeList.size(); ++i)
    {
        if(m_nodeList.at(i).value(ModelDepthKey).toInt() <= depth)
        {
            break;
        }
    }

    auto obj = QJsonObject(json);
    obj[ModelDepthKey] = depth + 1;
    obj[ModelExpendKey] = true;
    obj[ModelChildrenExpendKey] = false;
    obj[ModelHasChildrendKey] = false;

    beginInsertRows(QModelIndex(), i, i);
    m_nodeList.insert(i, obj);
    endInsertRows();
    countChanged();
    innerUpdate(index);
    expandTo(i);
    return i;
}

void CatModel::CatTreeModel::remove(int index)
{
    if(index < 0 || index >= m_nodeList.size())
    {
        return;
    }
    int depth = m_nodeList.at(index).value(ModelDepthKey).toInt();
    int i = index + 1;
    for(; i < m_nodeList.size(); ++i)
    {
        int childDepth = m_nodeList.at(i).value(ModelDepthKey).toInt();
        if(childDepth <= depth)
        {
            break;
        }
    }

    beginRemoveRows({}, index, i - 1);
    for(int j = 0; j < i - index; ++j)
    {
        m_nodeList.removeAt(index);
    }
    endRemoveRows();
    countChanged();
    if(depth > 0)
    {
        for(int j = index - 1; j >= 0; --j)
        {
            if(depth - 1 == m_nodeList.at(j).value(ModelDepthKey).toInt())
            {
                innerUpdate(j);
                break;
            }
        }
    }
}

QList<int> CatTreeModel::search(const QString &key, const QString &value, Qt::CaseSensitivity cs) const
{
    if(key.isEmpty() || value.isEmpty())
    {
        return {};
    }
    QList<int> ans;
    ans.reserve(m_nodeList.size());
    for(int i = 0; i < m_nodeList.size(); ++i)
    {
        if(m_nodeList.at(i).value(key).toString().contains(value, cs))
        {
            ans.push_back(i);
        }
    }
    return ans;
}

void CatTreeModel::expand(int index)
{
    if(index < 0 || index >= m_nodeList.size())
    {
        return;
    }
    int depth = m_nodeList.at(index).value(ModelDepthKey).toInt();
    for(int i = index + 1; i < m_nodeList.size(); ++i)
    {
        int childDepth = m_nodeList.at(i).value(ModelDepthKey).toInt();
        if(childDepth <= depth)
        {
            break;
        } else if(childDepth > depth + 1)
        {
            continue;
        }
        setNodeValue(i, ModelExpendKey, true);
    }
    setNodeValue(index, ModelChildrenExpendKey, true);
}

void CatModel::CatTreeModel::collapse(int index)
{
    if(index < 0 || index >= m_nodeList.size())
    {
        return;
    }
    int depth = m_nodeList.at(index).value(ModelDepthKey).toInt();
    for(int i = index + 1; i < m_nodeList.size(); ++i)
    {
        int childDepth = m_nodeList.at(i).value(ModelDepthKey).toInt();
        if(childDepth <= depth)
        {
            break;
        }
        setNodeValue(i, ModelExpendKey, false);
        setNodeValue(i, ModelChildrenExpendKey, false);
    }
    setNodeValue(index, ModelChildrenExpendKey, false);
}

void CatModel::CatTreeModel::expandTo(int index)
{
    if(index < 0 || index >= m_nodeList.size())
    {
        return;
    }
    int depth = m_nodeList.at(index).value(ModelDepthKey).toInt();
    int parentDepth = depth - 1;
    QList<int> indexList;
    for(int i = index - 1; i >= 0 && parentDepth >= 0; --i)
    {
        int childDepth = m_nodeList.at(i).value(ModelDepthKey).toInt();
        if(childDepth == parentDepth)
        {
            indexList.push_back(i);
            parentDepth --;
        }
    }
    for(auto i : indexList)
    {
        expand(i);
    }
}

void CatModel::CatTreeModel::expandAll()
{
    for(int i = 0; i < m_nodeList.size(); ++i)
    {
        if(true == m_nodeList.at(i).value(ModelHasChildrendKey).toBool())
        {
            setNodeValue(i, ModelChildrenExpendKey, true);
        }
        setNodeValue(i, ModelExpendKey, true);
    }
}

void CatModel::CatTreeModel::collapseAll()
{
    for(int i = 0; i < m_nodeList.size(); ++i)
    {
        if(true == m_nodeList.at(i).value(ModelHasChildrendKey).toBool())
        {
            setNodeValue(i, ModelChildrenExpendKey, false);
        }
        if(0 < m_nodeList.at(i).value(ModelDepthKey).toInt())
        {
            setNodeValue(i, ModelExpendKey, false);
        }
    }
}

int CatModel::CatTreeModel::count() const
{
    return m_nodeList.size();
}

QVariant CatModel::CatTreeModel::data(int idx, int role) const
{
    return Parent::data(Parent::index(idx), role);
}

void CatModel::CatTreeModel::gen(int depth, const QJsonArray &dataArray)
{
    for(auto i : dataArray)
    {
        auto obj = i.toObject();
        obj[ModelDepthKey] = depth;
        obj[ModelExpendKey] = true;
        obj[ModelChildrenExpendKey] = false;
        obj[ModelChildrenKey] = false;
        if(!m_recursionKey.isEmpty() && obj.contains(m_recursionKey))
        {
            auto arr = obj.value(m_recursionKey).toArray();
            if(!arr.isEmpty())
            {
                obj[ModelChildrenExpendKey] = true;
                obj[ModelChildrenKey] = true;
                obj.remove(m_recursionKey);
                m_nodeList.append(obj);
                gen(depth + 1, arr);
                continue;
            }
        }
        m_nodeList.append(obj);
    }
}

QJsonArray CatModel::CatTreeModel::getChildren(int parentIndex, int parentDepth) const
{
    QJsonArray arr;
    for(int i = parentIndex + 1; i < m_nodeList.size(); ++i)
    {
        int childDepth = m_nodeList.at(i).value(ModelDepthKey).toInt();
        if(childDepth == parentDepth + 1)
        {
            auto node = QJsonObject(m_nodeList.at(i));
            for(auto k : ModelFilterKeyList)
            {
                node.remove(k);
            }
            auto children = getChildren(i, childDepth);
            if(!children.isEmpty())
            {
                node[m_recursionKey] = children;
            }
            arr.append(node);
        } else if(childDepth <= parentDepth)
        {
            break;
        }
    }
    return arr;
}

int CatModel::CatTreeModel::addWithoutDepth(const QJsonObject &json)
{
    auto obj = QJsonObject(json);
    obj[ModelDepthKey] = 0;
    obj[ModelExpendKey] = true;
    obj[ModelChildrenExpendKey] = false;
    obj[ModelChildrenKey] = false;
    beginInsertRows(QModelIndex(), m_nodeList.count(), m_nodeList.count());
    m_nodeList.append(obj);
    endInsertRows();
    countChanged();
    return m_nodeList.count() - 1;
}

void CatModel::CatTreeModel::innerUpdate(int index)
{
    if(index < 0 || index >= m_nodeList.size())
    {
        return;
    }
    int depth = m_nodeList.at(index).value(ModelDepthKey).toInt();
    int childrenCount = 0;
    for(int i = index + 1; i < m_nodeList.size(); ++i)
    {
        int childDepth = m_nodeList.at(i).value(ModelDepthKey).toInt();
        if(childDepth <= depth)
        {
            break;
        } else if(childDepth == depth + 1)
        {
            childrenCount++;
        }
    }
}

}
