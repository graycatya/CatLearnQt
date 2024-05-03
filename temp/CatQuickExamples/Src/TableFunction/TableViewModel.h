#ifndef TABLEVIEWMODEL_H
#define TABLEVIEWMODEL_H

#include <QAbstractTableModel>
#include <QQmlParserStatus>
#include <QHash>
#include <QList>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

// Tebleview
class TableViewModel : public QAbstractTableModel, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(QStringList headerHor READ getHeaderHor WRITE setHeaderHor NOTIFY headerHorChanged)
    Q_PROPERTY(QJsonArray initData READ getInitData WRITE setInitData NOTIFY initDataChanged)

public:
    explicit TableViewModel(QObject *parent = nullptr);

    QStringList getHeaderHor() const;
    void setHeaderHor(const QStringList &header);

    QJsonArray getInitData() const;
    void setInitData(const QJsonArray &jsonArr);

    // QQmlParserStatus: 构造前
    void classBegin() override;
    // QQmlParserStatus: 构造后
    void componentComplete() override;
    // 自定义role
    QHash<int, QByteArray> roleNames() const override;

    // 表头
    QVariant headerData(int index, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setHeaderData(int index, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    // 数据,这三个必须实现
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // 编辑
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
    void loadData(const QJsonArray &data);

signals:
    void headerHorChanged();
    void initDataChanged();

private:
    bool m_pLoadSucceed = false;
    QJsonArray m_pInitData;
    QVector<QVector<QVariant>> m_pModelData;
    QList<QString> m_pHeaderHorList;
};

#endif // TABLEVIEWMODEL_H
