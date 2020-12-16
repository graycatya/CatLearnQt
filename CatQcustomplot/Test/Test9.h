#ifndef TEST9_H
#define TEST9_H

#include <QWidget>

namespace Ui {
class Test9;
}

class Test9 : public QWidget
{
    Q_OBJECT

public:
    explicit Test9(QWidget *parent = nullptr);
    ~Test9();

private:
    void InitUi();
    void InitProperty();

private:
    Ui::Test9 *ui;
};

#endif // TEST9_H
