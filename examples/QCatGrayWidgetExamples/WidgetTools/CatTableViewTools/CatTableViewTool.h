#ifndef CATTABLEVIEWTOOL_H
#define CATTABLEVIEWTOOL_H

#include "CatControl/CatTableViewBasics.h"
#include "CatTableItemDelegate.h"
#include "CatTableModel.h"

class CatTableViewTool : public CatTableViewBasics
{
    Q_OBJECT
public:
    explicit CatTableViewTool(QWidget *parent = nullptr);
    ~CatTableViewTool();

    CatTableModel *GetModel() { return dataModel; }

    void AddData(bool state = false, QString times = "");

    void ClearTable();

private:
      void InitUi();
      void InitProperty();
      void InitConnect();
      void InitTableHead();

protected:
      bool eventFilter(QObject *object, QEvent *event);
      void resizeEvent(QResizeEvent *event);

signals:
    void checkRect(QRect rect);
    void hoverIndexChanged(const QModelIndex &index);

private:
    CatTableModel* dataModel = nullptr;
    CatTableItemDelegate *delegate = nullptr;
    int m_TotalSelectDataNums = 0;  // 当前表格选中的数据
    int m_TotalDataNums = 0;    // 当前表格总数据
};

#endif // CATTABLEVIEWTOOL_H
