#ifndef INPUTTOOLS_H
#define INPUTTOOLS_H

#include <QWidget>
#include "QCatGrayFlowLayout.h"

namespace Ui {
class InputTools;
}

class InputTools : public QWidget
{
    Q_OBJECT

public:
    explicit InputTools(QWidget *parent = nullptr);
    ~InputTools();

private:
    void InitUi();
    void InitProperty();
    void InitConnect();

    void UpdateStyle();

    void InitDefauleSlider();

private:
    Ui::InputTools *ui;
    QCatGrayFlowLayout *m_pCatFlowLayout = nullptr;
};

#endif // INPUTTOOLS_H
