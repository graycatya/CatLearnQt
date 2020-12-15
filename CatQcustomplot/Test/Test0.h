#ifndef TEST0_H
#define TEST0_H

#include <QWidget>

namespace Ui {
class Test0;
}

class Test0 : public QWidget
{
    Q_OBJECT

public:
    explicit Test0(QWidget *parent = nullptr);
    ~Test0();

private:
    void InitUi();
    void InitProperty();

private:
    Ui::Test0 *ui;
};

#endif // TEST0_H
