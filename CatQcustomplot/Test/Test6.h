#ifndef TEST6_H
#define TEST6_H

#include <QWidget>

namespace Ui {
class Test6;
}

class Test6 : public QWidget
{
    Q_OBJECT

public:
    explicit Test6(QWidget *parent = nullptr);
    ~Test6();

private:
    void InitUi();
    void InitProperty();

private:
    Ui::Test6 *ui;
};

#endif // TEST6_H
