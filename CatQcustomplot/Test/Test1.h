#ifndef TEST1_H
#define TEST1_H

#include <QWidget>

namespace Ui {
class Test1;
}

class Test1 : public QWidget
{
    Q_OBJECT

public:
    explicit Test1(QWidget *parent = nullptr);
    ~Test1();

private:
    void InitUi();
    void InitProperty();


private:
    Ui::Test1 *ui;
};

#endif // TEST1_H
