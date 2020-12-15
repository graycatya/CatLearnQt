#ifndef TEST7_H
#define TEST7_H

#include <QWidget>

namespace Ui {
class Test7;
}

class Test7 : public QWidget
{
    Q_OBJECT

public:
    explicit Test7(QWidget *parent = nullptr);
    ~Test7();

private:
    void InitUi();
    void InitProperty();

private:
    Ui::Test7 *ui;
};

#endif // TEST7_H
