#ifndef TEST10_H
#define TEST10_H

#include <QWidget>
#include <QPen>

class QTimer;

namespace Ui {
class Test10;
}

class Test10 : public QWidget
{
    Q_OBJECT

public:
    explicit Test10(QWidget *parent = nullptr);
    ~Test10();

private slots:
    void on_pushButton_clicked();

private:
    void InitUi();
    void InitProperty();

private:
    Ui::Test10 *ui;
    QTimer *dataTimer;
    QPen pen;
};

#endif // TEST10_H
