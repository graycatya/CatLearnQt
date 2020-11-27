#ifndef CATDRAWINGBOARD_H
#define CATDRAWINGBOARD_H

#include <QWidget>

class CatGraphicsView;

namespace Ui {
class CatDrawingBoard;
}

class CatDrawingBoard : public QWidget
{
    Q_OBJECT

public:
    explicit CatDrawingBoard(QWidget *parent = nullptr);
    ~CatDrawingBoard();

public:
    CatGraphicsView* CreateBoard( void );

private:
    void InitUi();
    void InitProperty();

private:
    Ui::CatDrawingBoard *ui;
};

#endif // CATDRAWINGBOARD_H
