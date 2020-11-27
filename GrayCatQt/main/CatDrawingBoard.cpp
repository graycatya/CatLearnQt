#include "CatDrawingBoard.h"
#include "ui_CatDrawingBoard.h"
#include "CatGraphicsView/CatGraphicsView.h"
#include "CatGraphicsView/CatGraphicsScene.h"
#include "CatGraphicsView/TeachingTools/TeachingToolRuler.h"

CatDrawingBoard::CatDrawingBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CatDrawingBoard)
{
    ui->setupUi(this);
    InitUi();
    InitProperty();
}

CatDrawingBoard::~CatDrawingBoard()
{
    delete ui;
}

CatGraphicsView *CatDrawingBoard::CreateBoard()
{
    QWidget *widget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);

    CatGraphicsScene *scene = new CatGraphicsScene;
    scene->setBackgroundBrush(QBrush(QColor("#244242")));
    scene->setSceneRect(-5000, -5000, 10000, 10000);

    CatGraphicsView *view = new CatGraphicsView(this);
    view->setScene(scene);
    view->setRenderHints (QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    layout->addWidget(view);
    TeachingToolRuler *m_pTeachingToolRuler = new TeachingToolRuler;
    scene->addItem(m_pTeachingToolRuler);

    ui->GraphicsStacked->addWidget(widget);
    return view;
}

void CatDrawingBoard::InitUi()
{
    CreateBoard();
}

void CatDrawingBoard::InitProperty()
{

}
