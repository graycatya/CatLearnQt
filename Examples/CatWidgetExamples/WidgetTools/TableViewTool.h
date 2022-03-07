#ifndef TABLEVIEWTOOL_H
#define TABLEVIEWTOOL_H

#include <QWidget>

namespace Ui {
class TableViewTool;
}

class TableViewTool : public QWidget
{
    Q_OBJECT

public:
    struct TableData {
        bool state = false;
        QString time = "";
    };
    explicit TableViewTool(QWidget *parent = nullptr);
    ~TableViewTool();


private:
    void InitUi();
    void InitProperty();
    void InitConnect();

    void UpdateStyle();

    void onCurrentPage(int page);

private:
    Ui::TableViewTool *ui;
    QList<TableData> TableDatas;
};

#endif // TABLEVIEWTOOL_H
