#include "TableViewModel.h"


TableViewModel::TableViewModel(QObject *parent)
    : QAbstractTableModel(parent)
{

}

QStringList TableViewModel::getHeaderHor() const
{
    return m_pHeaderHorList;
}

void TableViewModel::setHeaderHor(const QStringList &header)
{
    m_pHeaderHorList = header;
    emit headerHorChanged();
}

QJsonArray TableViewModel::getInitData() const
{
    return m_pInitData;
}

void TableViewModel::setInitData(const QJsonArray &jsonArr)
{
    m_pInitData = jsonArr;
    if(m_pLoadSucceed) {
        loadData(m_pInitData);
    }

    emit initDataChanged();
}

void TableViewModel::classBegin()
{

}

void TableViewModel::componentComplete()
{
    m_pLoadSucceed = true;
    if(!m_pInitData.isEmpty())
    {
        loadData(m_pInitData);
    }
}

QHash<int, QByteArray> TableViewModel::roleNames() const
{
    // value 表示取值, edit表示编辑
    return QHash<int, QByteArray> {
        { Qt::DisplayRole, "value" },
        { Qt::EditRole, "edit" }
    };
}

QVariant TableViewModel::headerData(int index, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(orientation == Qt::Horizontal)
        {
            return m_pHeaderHorList.value(index, QString::number(index));
        } else if(orientation == Qt::Vertical)
        {
            return QString::number(index);
        }
    }

    return QVariant();
}

bool TableViewModel::setHeaderData(int index, Qt::Orientation orientation, const QVariant &value, int role)
{
    if(value != headerData(index, orientation, role))
    {
        if(orientation == Qt::Horizontal && role == Qt::EditRole)
        {
            m_pHeaderHorList[index] = value.toString();
            emit headerDataChanged(orientation, index, index);
            return true;
        }
    }
    return false;
}

int TableViewModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
    {
        return 0;
    }

    return m_pModelData.count();
}

int TableViewModel::columnCount(const QModelIndex &parent) const
{
    if(parent.isValid())
    {
        return 0;
    }

    return m_pHeaderHorList.count();
}

QVariant TableViewModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
    {
        return QVariant();
    }

    switch (role) {
        case Qt::DisplayRole:
        case Qt::EditRole:
        {
            return m_pModelData.at(index.row()).at(index.column());
        }
        default:
            break;
    }

    return QVariant();
}

bool TableViewModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(value.isValid()&&index.isValid() && (data(index, role) != value))
    {
        if(Qt::EditRole == role)
        {
            QJsonObject object = m_pModelData[index.row()][index.column()].toJsonObject();
            object.insert("Value", value.toJsonValue());
            m_pModelData[index.row()][index.column()] = object;
            emit dataChanged(index, index, QVector<int>() << role);
            return true;
        }
    }

    return false;
}

Qt::ItemFlags TableViewModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
    {
        return Qt::NoItemFlags;
    }

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

void TableViewModel::loadData(const QJsonArray &data)
{
    QVector<QVector<QVariant>> newData;
    QJsonArray::const_iterator iter;

    for(iter = data.begin(); iter != data.end(); ++iter)
    {
        QVector<QVariant> newRow;
        const QJsonObject itemRow = (*iter).toObject();

        newRow.append(itemRow.value("Id"));
        newRow.append(itemRow.value("Button"));
        newRow.append(itemRow.value("Logo"));
        newRow.append(itemRow.value("String"));
        newData.append(newRow);
    }

    emit beginResetModel();
    m_pModelData = newData;
    emit endResetModel();
}
