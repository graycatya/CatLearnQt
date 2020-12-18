#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "CatQcustomplot/CatQcustomplot.h"
#include <QDebug>

#include "Test/Test0.h"
#include "Test/Test1.h"
#include "Test/Test2.h"
#include "Test/Test3.h"
#include "Test/Test4.h"
#include "Test/Test5.h"
#include "Test/Test6.h"
#include "Test/Test7.h"
#include "Test/Test8.h"
#include "Test/Test9.h"
#include "Test/Test10.h"
#include "Test/Test11.h"
#include "Test/Test12.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitUi();
    InitProperty();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitUi()
{
    CatQcustomplot plot;
    qDebug() <<  plot.ScatterShapeList();
    qDebug() <<  plot.GraphLineStyleList();
    qDebug() << plot.BarsWidthType();
    ui->splitter->setStretchFactor(0, 1);
    ui->splitter->setStretchFactor(1, 9);

    Test0 *m_pTest_0 = new Test0(ui->page_0);
    QVBoxLayout *pagelayout_0 = new QVBoxLayout(ui->page_0);
    pagelayout_0->setContentsMargins(0,0,0,0);
    pagelayout_0->setSpacing(0);

    pagelayout_0->addWidget(m_pTest_0);

    Test1 *m_pTest_1 = new Test1(ui->page_1);
    QVBoxLayout *pagelayout_1 = new QVBoxLayout(ui->page_1);
    pagelayout_1->setContentsMargins(0,0,0,0);
    pagelayout_1->setSpacing(0);

    pagelayout_1->addWidget(m_pTest_1);

    Test2 *m_pTest_2 = new Test2(ui->page_2);
    QVBoxLayout *pagelayout_2 = new QVBoxLayout(ui->page_2);
    pagelayout_2->setContentsMargins(0,0,0,0);
    pagelayout_2->setSpacing(0);

    pagelayout_2->addWidget(m_pTest_2);

    Test3 *m_pTest_3 = new Test3(ui->page_3);
    QVBoxLayout *pagelayout_3 = new QVBoxLayout(ui->page_3);
    pagelayout_3->setContentsMargins(0,0,0,0);
    pagelayout_3->setSpacing(0);

    pagelayout_3->addWidget(m_pTest_3);

    Test4 *m_pTest_4 = new Test4(ui->page_4);
    QVBoxLayout *pagelayout_4 = new QVBoxLayout(ui->page_4);
    pagelayout_4->setContentsMargins(0,0,0,0);
    pagelayout_4->setSpacing(0);

    pagelayout_4->addWidget(m_pTest_4);

    Test5 *m_pTest_5 = new Test5(ui->page_5);
    QVBoxLayout *pagelayout_5 = new QVBoxLayout(ui->page_5);
    pagelayout_5->setContentsMargins(0,0,0,0);
    pagelayout_5->setSpacing(0);

    pagelayout_5->addWidget(m_pTest_5);

    Test6 *m_pTest_6 = new Test6(ui->page_6);
    QVBoxLayout *pagelayout_6 = new QVBoxLayout(ui->page_6);
    pagelayout_6->setContentsMargins(0,0,0,0);
    pagelayout_6->setSpacing(0);

    pagelayout_6->addWidget(m_pTest_6);

    Test7 *m_pTest_7 = new Test7(ui->page_7);
    QVBoxLayout *pagelayout_7 = new QVBoxLayout(ui->page_7);
    pagelayout_7->setContentsMargins(0,0,0,0);
    pagelayout_7->setSpacing(0);

    pagelayout_7->addWidget(m_pTest_7);

    Test8 *m_pTest_8 = new Test8(ui->page_8);
    QVBoxLayout *pagelayout_8 = new QVBoxLayout(ui->page_8);
    pagelayout_8->setContentsMargins(0,0,0,0);
    pagelayout_8->setSpacing(0);

    pagelayout_8->addWidget(m_pTest_8);

    Test9 *m_pTest_9 = new Test9(ui->page_9);
    QVBoxLayout *pagelayout_9 = new QVBoxLayout(ui->page_9);
    pagelayout_9->setContentsMargins(0,0,0,0);
    pagelayout_9->setSpacing(0);

    pagelayout_9->addWidget(m_pTest_9);

    Test10 *m_pTest_10 = new Test10(ui->page_10);
    QVBoxLayout *pagelayout_10 = new QVBoxLayout(ui->page_10);
    pagelayout_10->setContentsMargins(0,0,0,0);
    pagelayout_10->setSpacing(0);

    pagelayout_10->addWidget(m_pTest_10);

    Test11 *m_pTest_11 = new Test11(ui->page_11);
    QVBoxLayout *pagelayout_11 = new QVBoxLayout(ui->page_11);
    pagelayout_11->setContentsMargins(0,0,0,0);
    pagelayout_11->setSpacing(0);

    pagelayout_11->addWidget(m_pTest_11);

    Test12 *m_pTest_12 = new Test12(ui->page_12);
    QVBoxLayout *pagelayout_12 = new QVBoxLayout(ui->page_12);
    pagelayout_12->setContentsMargins(0,0,0,0);
    pagelayout_12->setSpacing(0);

    pagelayout_12->addWidget(m_pTest_12);

}

void MainWindow::InitProperty()
{

}

void MainWindow::on_ToolList_currentRowChanged(int currentRow)
{
    ui->ToolsStackedWidget->setCurrentIndex(currentRow);
}
