#ifndef CATDRAWINGBOARD_H
#define CATDRAWINGBOARD_H

#include <QWidget>

namespace Ui {
class CatDrawingBoard;
}

class CatDrawingBoard : public QWidget
{
    Q_OBJECT

public:
    explicit CatDrawingBoard(QWidget *parent = nullptr);
    ~CatDrawingBoard();

private:
    Ui::CatDrawingBoard *ui;
};

#endif // CATDRAWINGBOARD_H
