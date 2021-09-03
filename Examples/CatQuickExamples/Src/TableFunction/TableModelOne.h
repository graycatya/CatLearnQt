#ifndef TABLEMODELONE_H
#define TABLEMODELONE_H

#include <QAbstractTableModel>
#include <QQmlParserStatus>
#include <QHash>
#include <QList>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QObject>

class TableModelOne : public QAbstractItemModel, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(QStringList headerHor READ getHeaderHor WRITE setHeaderHor, NOTIFY headerHorChanged)
    Q_PROPERTY(QJsonArray tableData READ getTableData WRITE setTableData, NOTIFY tableDataChanged)
public:
    explicit TableModelOne(QObject *parent = nullptr);

    // QQmlParserStatus: 构造前
    void classBegin() override;
    // QQmlParserStatus: 构造后
    void componentComplete() override;

    QStringList getHeaderHor() const;
    void setHeaderHor(const QStringList &header);

    QJsonArray getTableData() const;
    void setTableData(const QJsonArray &jsonArr);

    // 自定义role
    QHash<int, QByteArray> roleNames() const override;

    // 表头
    QVariant headerData(int index, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setHeaderData(int index, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // 编辑
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;


signals:

};

#endif // TABLEMODELONE_H
