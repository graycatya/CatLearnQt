#include "CatDrawingBoard.h"
#include "ui_CatDrawingBoard.h"

CatDrawingBoard::CatDrawingBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CatDrawingBoard)
{
    ui->setupUi(this);
}

CatDrawingBoard::~CatDrawingBoard()
{
    delete ui;
}
