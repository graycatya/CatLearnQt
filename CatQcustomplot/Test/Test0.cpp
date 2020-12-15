#include "Test0.h"
#include "ui_Test0.h"

Test0::Test0(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Test0)
{
    ui->setupUi(this);
    InitUi();
    InitProperty();
}

Test0::~Test0()
{
    delete ui;
}

void Test0::InitUi()
{

}

void Test0::InitProperty()
{
    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                          QCP::iSelectLegend | QCP::iSelectPlottables);
    // 启动左上角图列
    ui->widget->legend->setVisible(true);

    // 生成2种随机的蜡烛图数据，第一个是蜡烛图数据，第二个是美国线数据
    int n = 500;
    QVector<double> time(n), value1(n), value2(n);
    QDateTime start = QDateTime(QDate(2014, 6, 11));
    start.setTimeSpec(Qt::UTC);
    double startTime = start.toTime_t();
    double binSize = 3600*24; // 1天的数据
    time[0] = startTime;
    value1[0] = 60;
    value2[0] = 20;
    // 生成随机数时给指定的种子，那么生成的随机数都是相同的，因此每次运行后得到的结果都是不变的
    qsrand(9);
    for(int i = 1; i < n; ++i)
    {
        time[i] = startTime + 3600 * i;
        value1[i] = value1[i-1] + (qrand()/(double)RAND_MAX-0.5)*10;
        value2[i] = value2[i-1] + (qrand()/(double)RAND_MAX-0.5)*3;
    }
    // 初始化一个蜡烛图指针
    QCPFinancial *candlesticks = new QCPFinancial(ui->widget->xAxis, ui->widget->yAxis);
    candlesticks->setName("Candlestick");
    // 设置图表类型为蜡烛图
    candlesticks->setChartStyle(QCPFinancial::csCandlestick);
    candlesticks->data()->set(QCPFinancial::timeSeriesToOhlc(time, value1, binSize, startTime));
    // 设置每一个数据项的绘制宽度
    candlesticks->setWidth(binSize*0.9);
    // 设置是否显示两种颜色
    candlesticks->setTwoColored(true);
    // 设置收>开画刷
    candlesticks->setBrushPositive(QColor(245, 245, 245));
    // 设置收<开画刷
    candlesticks->setBrushNegative(QColor(40, 40, 40));
    // 设置收>开画笔
    candlesticks->setPenPositive(QPen(QColor(0, 0, 0)));
    // 设置收<开画笔
    candlesticks->setPenNegative(QPen(QColor(0, 0, 0)));

    // 初始化一个美国线圈指针
    QCPFinancial *ohlc = new QCPFinancial(ui->widget->xAxis, ui->widget->yAxis);
    ohlc->setName("OHLC");
    // 设置图表类型为美国线
    ohlc->setChartStyle(QCPFinancial::csOhlc);
    //为了区分于蜡烛图显示
    ohlc->data()->set(QCPFinancial::timeSeriesToOhlc(time, value2, binSize/3.0, startTime));
    ohlc->setWidth(binSize*0.2);
    ohlc->setTwoColored(true);


    // 创建一个坐标轴矩形
    QCPAxisRect *volumeAxisRect = new QCPAxisRect(ui->widget);
    ui->widget->plotLayout()->addElement(1, 0, volumeAxisRect);
    volumeAxisRect->setMaximumSize(QSize(QWIDGETSIZE_MAX, 100));
    volumeAxisRect->axis(QCPAxis::atBottom)->setLayer("axes");
    volumeAxisRect->axis(QCPAxis::atBottom)->grid()->setLayer("grid");

    // 设置自己构造的坐标轴矩形属性
    ui->widget->plotLayout()->setRowSpacing(0);
    volumeAxisRect->setAutoMargins(QCP::msLeft | QCP::msRight | QCP::msBottom);
    volumeAxisRect->setMargins(QMargins(0,0,0,0));

    // 生成两种颜色的柱状图
    // 是否自动生成图列
    ui->widget->setAutoAddPlottableToLegend(false);
    QCPBars *volumePos = new QCPBars(volumeAxisRect->axis(QCPAxis::atBottom), volumeAxisRect->axis(QCPAxis::atLeft));
    QCPBars *volumeNeg = new QCPBars(volumeAxisRect->axis(QCPAxis::atBottom), volumeAxisRect->axis(QCPAxis::atLeft));

    for(int i = 0; i < n/5; ++i)
    {
        int v = qrand()%20000 + qrand()%20000 + qrand()%20000 - 10000*3;
        // 构造随机数据
        (v < 0 ? volumeNeg : volumePos)->addData(startTime+3000*5.0*i, qAbs(v));
    }

    volumePos->setWidth(3000*4);
    volumePos->setPen(Qt::NoPen);
    volumePos->setBrush(QColor(100, 100, 110));
    volumeNeg->setWidth(3000*4);
    volumeNeg->setPen(Qt::NoPen);
    volumeNeg->setBrush(QColor(180, 90, 90));

    // 设置自己构造的坐标轴矩形的x轴和QCustomPlot中的坐标轴矩形(默认的会生成一个)x轴同步，两个坐标轴永远显示的坐标范围是一样的
    connect(ui->widget->xAxis, SIGNAL(rangeChanged(QCPRange)), volumeAxisRect->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));
    connect(volumeAxisRect->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), ui->widget->xAxis, SLOT(setRange(QCPRange)));

    // 构造一个新的坐标刻度计算类
    QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
    dateTimeTicker->setDateTimeSpec(Qt::UTC);
    dateTimeTicker->setDateTimeFormat("dd.MMMM");
    // 赋予自己构造的坐标轴矩形的x轴一个新的刻度计算类
    volumeAxisRect->axis(QCPAxis::atBottom)->setTicker(dateTimeTicker);
    volumeAxisRect->axis(QCPAxis::atBottom)->setTickLabelRotation(15);
    // 不显示坐标轴文本
    ui->widget->xAxis->setTickLabels(false);
    // 这个接口实现不友好
    ui->widget->xAxis->setTicks(false);
    // 赋予默认的坐标轴矩形的x轴一个新的刻度计算类
    ui->widget->xAxis->setTicker(dateTimeTicker);
    // 重新调整坐标轴，使绘图中的所有情节图(如图表)都完全可见 - 调整后数据就刷新出来了
    ui->widget->rescaleAxes();
    ui->widget->xAxis->scaleRange(1.025, ui->widget->xAxis->range().center());
    ui->widget->yAxis->scaleRange(1.1, ui->widget->yAxis->range().center());

    // 设置两个坐标轴矩形左右对齐
    QCPMarginGroup *group = new QCPMarginGroup(ui->widget);
    ui->widget->axisRect()->setMarginGroup(QCP::msLeft|QCP::msRight, group);
    volumeAxisRect->setMarginGroup(QCP::msLeft | QCP::msRight, group);

}
