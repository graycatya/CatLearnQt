#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QPainterPath>
#include <QPainter>
#include <QtMath>

MainWindow::MainWindow(QWidget *parent) :
    CatFramelessMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitFrameless();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    PaintShadow(&painter, QColor(0, 0, 0, 50), 8, 3);
}

void MainWindow::InitFrameless()
{
    this->setTitleBar(ui->TitleWidget);

    //设置样式表
    QStringList list;
    list << "#TitleWidget{background:#BBBBBB;}";
    //list << "#TitleWidget{border-top-left-radius:8px;border-top-right-radius:8px;}";
    list << "#WorkWidget{border:0px solid #BBBBBB;background:#FFFFFF;}";
    //list << "#WorkWidget{border-bottom-left-radius:8px;border-bottom-right-radius:8px;}";
    this->setStyleSheet(list.join(""));
}

void MainWindow::PaintShadow(QPainter *painter, QColor shadowcolor, int shadowwidth, qreal radius)
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRoundedRect(shadowwidth, shadowwidth,
                 this->width()-shadowwidth*2, this->height()-shadowwidth*2, radius, radius);


    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->fillPath(path, QBrush(Qt::white));

    QColor color = shadowcolor;
    for(int i=0; i<shadowwidth; i++)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRoundedRect(shadowwidth-i, shadowwidth-i,
                     this->width()-(shadowwidth-i)*2,
                     this->height()-(shadowwidth-i)*2, radius, radius);
        color.setAlpha(150 - qSqrt(i)*50);
        painter->setPen(color);
        painter->drawPath(path);
    }
}


