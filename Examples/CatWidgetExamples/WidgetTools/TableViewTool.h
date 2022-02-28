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
    explicit TableViewTool(QWidget *parent = nullptr);
    ~TableViewTool();

private:
    void InitUi();
    void InitProperty();
    void InitConnect();

    void UpdateStyle();

private:
    Ui::TableViewTool *ui;
};

#endif // TABLEVIEWTOOL_H
