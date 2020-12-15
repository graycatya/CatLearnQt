#ifndef TEST8_H
#define TEST8_H

#include <QWidget>

namespace Ui {
class Test8;
}

class Test8 : public QWidget
{
    Q_OBJECT

public:
    explicit Test8(QWidget *parent = nullptr);
    ~Test8();

private:
    void InitUi();
    void InitProperty();

private:
    Ui::Test8 *ui;
};

#endif // TEST8_H
