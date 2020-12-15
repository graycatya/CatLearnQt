#ifndef TEST5_H
#define TEST5_H

#include <QWidget>

namespace Ui {
class Test5;
}

class QCPItemTracer;
class QTimer;

class Test5 : public QWidget
{
    Q_OBJECT

public:
    explicit Test5(QWidget *parent = nullptr);
    ~Test5();

private:
    void InitUi();
    void InitProperty();

private:
    Ui::Test5 *ui;
    QCPItemTracer *itemDemoPhaseTracer;
    QTimer* dataTimer;
};

#endif // TEST5_H
