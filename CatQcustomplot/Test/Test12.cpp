#include "Test12.h"
#include "ui_Test12.h"

Test12::Test12(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Test12)
{
    ui->setupUi(this);
    InitUi();
    InitProperty();
    InitConnect();
}

Test12::~Test12()
{
    delete ui;
}

void Test12::InitUi()
{
    ui->splitter->setStretchFactor(0, 2);
    ui->splitter->setStretchFactor(1, 8);
    ui->comboBox->addItems(ui->widget->ScatterShapeList());
    ui->comboBox_2->addItems(ui->widget->GraphLineStyleList());
    ui->comboBox_3->addItems(ui->widget->BarsWidthType());
}

void Test12::InitProperty()
{
    CatLineChart *plot = ui->widget;
    plot->legend->setVisible(true);
    plot->SetLegenAlignment(0, Qt::AlignTop | Qt::AlignHCenter);
    plot->AddGraph(QColor(40, 110, 255), "test1");
    plot->AddGraph(QColor(255, 110, 40), "test2");

    //ticker->setDateTimeFormat("yyyy-MM-dd hh:mm:ss");
    QSharedPointer<QCPAxisTickerDateTime> timeTicker(new QCPAxisTickerDateTime);
    timeTicker->setDateTimeFormat("yyyy-MM-dd hh:mm:ss");
    plot->xAxis->setTicker(timeTicker);
    plot->replot();
}

void Test12::InitConnect()
{

}
