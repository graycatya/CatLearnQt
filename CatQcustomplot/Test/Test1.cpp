#include "Test1.h"
#include "ui_Test1.h"

Test1::Test1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Test1)
{
    ui->setupUi(this);
    InitUi();
    InitProperty();
}

Test1::~Test1()
{
    delete ui;
}

void Test1::InitUi()
{

}

void Test1::InitProperty()
{
    ui->widget->legend->setVisible(true);
    ui->widget->legend->setFont(QFont("Helvetica", 9));
    QPen pen;

    // 设置图例的文本
    QStringList lineNames;
    lineNames << "lsNone" << "lsLine" << "lsStepLeft" << "leStepRight" << "leStepCenter" << "lsImpulse";

    for(int i = QCPGraph::lsNone; i <= QCPGraph::lsImpulse; ++i)
    {
        ui->widget->addGraph();
        pen.setColor(QColor(qSin(i * 1 + 1.2) * 80 + 80, qSin(i * 0.3 + 0) * 80 + 80, qSin(i * 0.3 + 1.5) * 80 + 80));
        ui->widget->graph()->setPen(pen);
        ui->widget->graph()->setName(lineNames.at(i - QCPGraph::lsNone));
        // 设置线性
        ui->widget->graph()->setLineStyle((QCPGraph::LineStyle)i);
        // 设置每个节点数据绘制风格，默认是空，这里设置为空心圆
        ui->widget->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));

        QVector<double> x(15), y(15);
        for(int j = 0; j < 15; ++j)
        {
            x[j] = j / 15.0 * 5 * 3.14 + 0.01;
            y[j] = 7 * qSin(x[j]) / x[j] - (i - QCPGraph::lsNone) * 5 + (QCPGraph::lsImpulse) * 5 + 2;
        }
        ui->widget->graph()->setData(x, y);
        // 坐标轴自适应
        ui->widget->graph()->rescaleAxes(true);
    }

    ui->widget->yAxis->scaleRange(1.1, ui->widget->yAxis->range().center());
    ui->widget->xAxis->scaleRange(1.1, ui->widget->xAxis->range().center());

    // x轴不显示刻度
    ui->widget->xAxis->setTicks(false);
    // y轴显示刻度
    ui->widget->yAxis->setTicks(true);
    // x轴不显示文本
    ui->widget->xAxis->setTickLabels(false);
    // y轴显示文本
    ui->widget->yAxis->setTickLabels(true);
    /*
     * 一个默认的坐标轴矩形配置，包括：顶部坐标轴跟随底部坐标轴同步、
     * 右侧坐标轴跟随左侧坐标轴同步，不仅仅是坐标轴范围跟随同步，
     * 包括文本精度、文本格式、坐标轴类型、是否自动生成刻度、刻度间距等等。
    */
    ui->widget->axisRect()->setupFullAxesBox();
}
