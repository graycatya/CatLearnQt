#ifndef QRENCODETOOL_H
#define QRENCODETOOL_H

#include <QWidget>

class GernerateQRCode;

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
    void InitProperty();
    void InitConnect();

    void UpdateQrenCode();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;

private:
    Ui::QrenCodeTool *ui;
    GernerateQRCode *m_pGernerateQRCode;
};

#endif // QRENCODETOOL_H
