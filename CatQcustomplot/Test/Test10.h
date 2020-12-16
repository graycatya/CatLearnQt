#ifndef TEST10_H
#define TEST10_H

#include <QWidget>

namespace Ui {
class Test10;
}

class Test10 : public QWidget
{
    Q_OBJECT

public:
    explicit Test10(QWidget *parent = nullptr);
    ~Test10();

private:
    Ui::Test10 *ui;
};

#endif // TEST10_H
