#ifndef RIMLESSWINDOWTOOL_H
#define RIMLESSWINDOWTOOL_H

#include <QWidget>

namespace Ui {
class RimlessWindowTool;
}

class RimlessWindowTool : public QWidget
{
    Q_OBJECT

public:
    explicit RimlessWindowTool(QWidget *parent = nullptr);
    ~RimlessWindowTool();

private:
    Ui::RimlessWindowTool *ui;
};

#endif // RIMLESSWINDOWTOOL_H
