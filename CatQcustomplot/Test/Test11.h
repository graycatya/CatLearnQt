#ifndef TEST11_H
#define TEST11_H

#include <QWidget>

namespace Ui {
class Test11;
}

class Test11 : public QWidget
{
    Q_OBJECT

public:
    explicit Test11(QWidget *parent = nullptr);
    ~Test11();

private:
    void InitUi();
    void InitProperty();

private:
    Ui::Test11 *ui;
};

#endif // TEST11_H
