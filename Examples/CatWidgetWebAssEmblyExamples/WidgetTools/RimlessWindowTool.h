#ifndef RIMLESSWINDOWTOOL_H
#define RIMLESSWINDOWTOOL_H

#include <QWidget>
class RimlessWindow;

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
    void InitUi();
    void InitProperty();
    void InitConnect();

    void UpdateStyle();

protected:
    bool eventFilter(QObject *watched, QEvent *event);


private:
    Ui::RimlessWindowTool *ui;
    RimlessWindow *m_pRimlessWindow;

};

#endif // RIMLESSWINDOWTOOL_H
