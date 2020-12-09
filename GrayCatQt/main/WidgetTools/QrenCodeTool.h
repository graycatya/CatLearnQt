#ifndef QRENCODETOOL_H
#define QRENCODETOOL_H

#include <QWidget>

namespace Ui {
class QrenCodeTool;
}

class QrenCodeTool : public QWidget
{
    Q_OBJECT

public:
    explicit QrenCodeTool(QWidget *parent = nullptr);
    ~QrenCodeTool();

private:
    Ui::QrenCodeTool *ui;
};

#endif // QRENCODETOOL_H
