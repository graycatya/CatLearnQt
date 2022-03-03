#ifndef CATTABLEMODEL_H
#define CATTABLEMODEL_H

#include <QObject>
#include <QStandardItemModel>

class CatTableModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit CatTableModel(QObject *parent = nullptr);
    ~CatTableModel();
};

#endif // CATTABLEMODEL_H
