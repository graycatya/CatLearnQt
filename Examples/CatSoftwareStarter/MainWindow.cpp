#include "MainWindow.h"
#include "ui_MainWindow.h"

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

void MainWindow::InitFrameless()
{
    this->setTitleBar(ui->TitleWidget);

    //设置样式表
    QStringList list;
    list << "#TitleWidget{background:#BBBBBB;}";
    list << "#TitleWidget{border-top-left-radius:8px;border-top-right-radius:8px;}";
    list << "#WorkWidget{border:2px solid #BBBBBB;background:#FFFFFF;}";
    //list << "#WorkWidget{border-bottom-left-radius:8px;border-bottom-right-radius:8px;}";
    this->setStyleSheet(list.join(""));
}
