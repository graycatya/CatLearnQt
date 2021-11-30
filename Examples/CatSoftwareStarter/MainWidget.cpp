#include "MainWidget.h"
#include "ui_MainWidget.h"

MainWidget::MainWidget(QWidget *parent) :
    CatFramelessWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    InitFrameless();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::InitFrameless()
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
