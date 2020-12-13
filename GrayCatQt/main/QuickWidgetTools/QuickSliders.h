#ifndef QUICKSLIDERS_H
#define QUICKSLIDERS_H

#include <QWidget>

namespace Ui {
class QuickSliders;
}

class QuickSliders : public QWidget
{
    Q_OBJECT

public:
    explicit QuickSliders(QWidget *parent = nullptr);
    ~QuickSliders();

private:
    Ui::QuickSliders *ui;
};

#endif // QUICKSLIDERS_H
