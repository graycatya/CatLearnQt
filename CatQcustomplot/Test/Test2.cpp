#include "Test2.h"
#include "ui_Test2.h"

Test2::Test2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Test2)
{
    ui->setupUi(this);
    InitUi();
    InitProperty();
}

Test2::~Test2()
{
    delete ui;
}

void Test2::InitUi()
{

}

void Test2::InitProperty()
{
    // 构造一个文本
    QCPItemText *phaseTracerText = new QCPItemText(ui->widget);
    //ui->widget->insertphaseTracerText);
    // 设置文本坐标解析方式，前文中有提到QCPItemPosition类的PositionType枚举
    phaseTracerText->position->setType(QCPItemPosition::ptAxisRectRatio);
    // 设置位置在矩形区域的位置
    phaseTracerText->setPositionAlignment(Qt::AlignRight | Qt::AlignBottom);
    // 设置位置，注意第三行代码的枚举类型和这儿的值解析方式有关系
    phaseTracerText->position->setCoords(1.0, 0.95);
    phaseTracerText->setText(QString("graycatya"));
    // 设置文本在矩形区域的位置
    phaseTracerText->setTextAlignment(Qt::AlignLeft);
    phaseTracerText->setFont(QFont(font().family(), 9));
    phaseTracerText->setPadding(QMargins(8, 0, 0, 0));

    QCPItemCurve *phaseTracerArrow = new QCPItemCurve(ui->widget);//构造一个带参数线
    //ui->widget->addItem(phaseTracerArrow);//添加到图中
    phaseTracerArrow->start->setParentAnchor(phaseTracerText->left);//曲线的开始点为文本的左位置
    phaseTracerArrow->startDir->setParentAnchor(phaseTracerArrow->start);//同步自身的锚点
    phaseTracerArrow->startDir->setCoords(-40, 0); // x轴偏移40个像素
    //phaseTracerArrow->end->setParentAnchor(phaseTracer->position);//曲线的结束点为实心圆的位置
    phaseTracerArrow->end->setCoords(10, 10);//偏移
    phaseTracerArrow->endDir->setParentAnchor(phaseTracerArrow->end);//同步自身的锚点
    phaseTracerArrow->endDir->setCoords(30, 30);//偏移
    phaseTracerArrow->setHead(QCPLineEnding::esSpikeArrow);//设置首部形状(箭头)
    //phaseTracerArrow->setTail(QCPLineEnding(QCPLineEnding::esBar, (phaseTracerText->bottom->pixelPoint().y() - phaseTracerText->top->pixelPoint().y())*0.85));//设置尾部形状(一条竖线)
}
