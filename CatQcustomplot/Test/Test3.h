#ifndef TEST3_H
#define TEST3_H

#include <QWidget>

namespace Ui {
class Test3;
}

class Test3 : public QWidget
{
    Q_OBJECT

public:
    explicit Test3(QWidget *parent = nullptr);
    ~Test3();

private:
    void InitUi();
    void InitProperty();

private:
    Ui::Test3 *ui;
};

#endif // TEST3_H
