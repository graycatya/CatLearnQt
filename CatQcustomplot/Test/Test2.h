#ifndef TEST2_H
#define TEST2_H

#include <QWidget>

namespace Ui {
class Test2;
}

class Test2 : public QWidget
{
    Q_OBJECT

public:
    explicit Test2(QWidget *parent = nullptr);
    ~Test2();

private:
    void InitUi();
    void InitProperty();


private:
    Ui::Test2 *ui;
};

#endif // TEST2_H
