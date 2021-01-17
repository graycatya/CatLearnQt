#ifndef QUICKQRENCODE_H
#define QUICKQRENCODE_H

#include <QWidget>

namespace Ui {
class QuickQrenCode;
}

class QuickQrenCode : public QWidget
{
    Q_OBJECT

public:
    explicit QuickQrenCode(QWidget *parent = nullptr);
    ~QuickQrenCode();

private:
    void InitProperty();
    void InitConnect();


private:
    Ui::QuickQrenCode *ui;
};

#endif // QUICKQRENCODE_H
