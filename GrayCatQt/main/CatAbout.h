#ifndef CATABOUT_H
#define CATABOUT_H

#include <QWidget>

namespace Ui {
class CatAbout;
}

class CatAbout : public QWidget
{
    Q_OBJECT

public:
    explicit CatAbout(QWidget *parent = nullptr);
    ~CatAbout();

private:
    void InitUi();
    void InitProperty();
    void InitConnect();

private:
    Ui::CatAbout *ui;
};

#endif // CATABOUT_H
