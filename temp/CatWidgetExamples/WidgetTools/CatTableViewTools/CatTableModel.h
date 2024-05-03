#ifndef CATTABLEMODEL_H
#define CATTABLEMODEL_H

#include <QObject>
#include <QStandardItemModel>
#include <QTableView>

struct Model_Structure
{
    int check;
    int id;
    bool state;
    QString time;
};

class CatTableModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit CatTableModel(QObject *parent = nullptr);
    ~CatTableModel();

    void AddData(Model_Structure data);
    void AddData(QList<Model_Structure> datas);
    void Clear();

    void SetCatTableViewTool(QTableView *view);

protected:
    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder);

private:
    QList<Model_Structure> m_yTableDatas;
    QTableView *m_pCatTableViewTool = nullptr;
};

#endif // CATTABLEMODEL_H
