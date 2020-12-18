#ifndef TEST12_H
#define TEST12_H

#include <QWidget>

namespace Ui {
class Test12;
}

class Test12 : public QWidget
{
    Q_OBJECT

public:
    explicit Test12(QWidget *parent = nullptr);
    ~Test12();

private:
    Ui::Test12 *ui;
};

#endif // TEST12_H
