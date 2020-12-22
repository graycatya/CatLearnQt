#include "CatLineChart.h"
#include "ui_CatLineChart.h"

#include "../../CatConfig/CatConfig.h"

#include <CatLog>

CatLineChart::CatLineChart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CatLineChart),
    m_pDataTimer(new QTimer(this))
{
    ui->setupUi(this);
    InitUi();
    InitProperty();
    InitConnect();
    InitChartConnect();
}

CatLineChart::~CatLineChart()
{
    if(m_pDataTimer != nullptr)
    {
        if(m_pDataTimer->isActive())
        {
            m_pDataTimer->stop();
        }
        m_pDataTimer->stop();
    }
    delete ui;
}

void CatLineChart::InitUi()
{
    ui->RootLayout->setStretchFactor(ui->FunctionWidget, 1);
    ui->RootLayout->setStretchFactor(ui->ChartWidget, 9);
    QListView *view_0 = new QListView();
    view_0->setObjectName("StyleComboBoxView");
    ui->ScatterShapeBox->setView(view_0);
    ui->ScatterShapeBox->addItems(ui->ChartWidget->ScatterShapeList());
    QListView *view_1 = new QListView();
    view_1->setObjectName("StyleComboBoxView");
    ui->LineStyleBox->setView(view_1);
    ui->LineStyleBox->addItems(ui->ChartWidget->GraphLineStyleList());
    ui->LineStyleBox->setCurrentIndex(1);
    StartTimer(false);

    // 支持opengl
    QLabel *m_pDXVALabel = new QLabel(ui->FunctionWidget);
    m_pDXVALabel->setObjectName(QString::fromUtf8("DxvaLabel"));
    ui->formLayout->setWidget(2, QFormLayout::LabelRole, m_pDXVALabel);

    m_pDXVALabel->setText(QCoreApplication::translate("CatLineChart", "DxVa:", nullptr));

    m_pDxvaBox = new QComboBox(ui->FunctionWidget);
    m_pDxvaBox->setObjectName(QString::fromUtf8("DxvaBox"));
    ui->formLayout->setWidget(2, QFormLayout::FieldRole, m_pDxvaBox);

    QListView *view_2 = new QListView();
    view_2->setObjectName("StyleComboBoxView");
    m_pDxvaBox->setView(view_2);

    m_pDxvaBox->addItems({"Not", "OpenGL"});

}


void CatLineChart::InitProperty()
{
    UpdateStyle();
    InitCharts();
}

void CatLineChart::InitConnect()
{
    connect(CatConfig::Instance(), &CatConfig::UpdateStyleSheets, this, [=](){
        UpdateStyle();
    });

    connect(ui->StartButton, &QPushButton::clicked, this, [=](){
        if(m_pDataTimer->isActive())
        {
            m_pDataTimer->stop();
            StartTimer(false);
            ui->ChartWidget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                                             QCP::iSelectAxes | QCP::iSelectLegend |
                                             QCP::iSelectPlottables);
        } else {
            m_pDataTimer->start(20);
            StartTimer(true);
            ui->ChartWidget->setInteractions(QCP::iRangeZoom | QCP::iSelectAxes |
                                             QCP::iSelectLegend | QCP::iSelectPlottables );
        }
    });
}

void CatLineChart::UpdateStyle()
{
    QString stylePath;
    if(CatConfig::ConfigExist())
    {
        stylePath = ":/qss/" + CatConfig::GetValue("style", "Defaule").toString() + "/";
        QString icon = ":/Images/" + CatConfig::GetValue("style", "Defaule").toString() + "/";
        this->setWindowIcon(QIcon(icon + "CATicon.png"));
    } else {
        stylePath = ":/qss/CatGray/";
        this->setWindowIcon(QIcon(":/Images/CatGray/CATicon.png"));
    }

    QFile file_0(stylePath + "CatLineChart.css");
    file_0.open(QIODevice::ReadOnly);
    QString stylehoot_0 = QLatin1String(file_0.readAll());
    this->setStyleSheet(stylehoot_0);
    file_0.close();
}

void CatLineChart::InitCharts()
{
    CatQcustomplot *customPlot = ui->ChartWidget;
    customPlot->legend->setVisible(true);
    customPlot->legend->setSelectedIconBorderPen(QPen(Qt::gray));
    customPlot->SetGraphSelectionDecoratorWidth(3);
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop | Qt::AlignLeft);
    for(int i = 0; i < 4; i++)
    {
       customPlot->addGraph();
       m_pGraphs.push_back(customPlot->graph());
       QPen pen;
       pen.setWidth(3);
       pen.setColor(QColor(qSin(i * 1 + 1.2) * 80 + 80, qSin(i*0.3 + 0) * 80 + 80, qSin(i*0.3 + 1.5) * 80 + 80));
       customPlot->graph()->setPen(pen);
       customPlot->graph()->setName(QString("Line %1").arg(QString::number(i)));
       customPlot->graph()->setLineStyle((QCPGraph::LineStyle)ui->LineStyleBox->currentIndex());//设置线性
       //设置每个节点数据绘制风格，默认是空，这里设置为空心圆
       customPlot->graph()->setScatterStyle(QCPScatterStyle(
                            (QCPScatterStyle::ScatterShape)ui->ScatterShapeBox->currentIndex(), 5));

       QSharedPointer<QCPAxisTickerDateTime> timeTicker(new QCPAxisTickerDateTime);
       timeTicker->setDateTimeFormat("yyyy-MM-dd hh:mm:ss");
       customPlot->xAxis->setTicker(timeTicker);
       /*
           便利功能，可在尚未有任何轴的每一侧创建一个轴，并将其可见性设置为true。
           此外，为上/右轴分配了下/左轴的以下属性：
           范围（QCPAxis :: setRange）
           范围反转（QCPAxis :: setRangeReversed）
           比例尺类型（QCPAxis :: setScaleType）
           刻度可见性（QCPAxis :: setTicks）
           数字格式（QCPAxis :: setNumberFormat）
           数字精度（QCPAxis :: setNumberPrecision）
           股票代号的股票代号（QCPAxisTicker :: setTickCount）
           股票行情的股票行情起源（QCPAxisTicker :: setTickOrigin）
       */
       customPlot->axisRect()->setupFullAxesBox();
       customPlot->yAxis->setRange(0.0, 100.0);

    }
}

void CatLineChart::InitChartConnect()
{
    QCustomPlot *customPlot = ui->ChartWidget;
    connect(ui->ScatterShapeBox, SIGNAL(currentIndexChanged(int)), this, SLOT(UpdateGraphScatterStyle(int)));
    connect(ui->LineStyleBox, SIGNAL(currentIndexChanged(int)), this, SLOT(UpdateGraphLineStyle(int)));
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(On_MousePress()));

    connect(m_pDxvaBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(On_UpdateDxva(QString)));

    // 用户更改QCustomPlot中的选择后（例如通过单击），将发出此信号。
    connect(customPlot, &QCustomPlot::selectionChangedByUser, this, [=](){
        // 使上下轴同步选择，并将轴和tick标签作为一个可选择对象处理:
        // make top and bottom axes be selected synchronously, and handle axis and tick labels as one selectable object:
        if (customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || customPlot->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
          customPlot->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) || customPlot->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
        {
            customPlot->xAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
            customPlot->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
        }
        // 使左右轴同步选择，并将轴和tick标签作为一个可选择对象处理:
        // make left and right axes be selected synchronously, and handle axis and tick labels as one selectable object:
        if (customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || customPlot->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
          customPlot->yAxis2->selectedParts().testFlag(QCPAxis::spAxis) || customPlot->yAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
        {
            customPlot->yAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
            customPlot->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
        }
        for (int i = 0; i < customPlot->graphCount(); ++i)
        {
            QCPGraph *graph = customPlot->graph(i);

            QCPPlottableLegendItem *item = customPlot->legend->itemWithPlottable(graph);
            if (item->selected() || graph->selected())//选中了哪条曲线或者曲线的图例
            {
                graph->selectionDecorator()->setPen(ui->ChartWidget->GetGraphSelectionDecoratorPen());
                item->setSelected(true);//同时选中曲线和图例
                graph->setSelection(QCPDataSelection(graph->data()->dataRange()));
            }
        }

    });

    // 定时更新动态数据
    connect(m_pDataTimer, &QTimer::timeout, this, [=](){

        double currtime = (double)(QDateTime::currentMSecsSinceEpoch()) / 1000.0;
        qsrand(currtime);

        static double lastPointKey = 0;
        if (currtime-lastPointKey > 0.5) // at most add point every 2 ms
        {
          // add data to lines:
          for(auto temp : m_pGraphs)
          {
              temp->addData(currtime, qrand() % 100);
          }
          lastPointKey = currtime;
        }
        // make key axis range scroll with the data (at a constant range size of 8):
        customPlot->xAxis->setRange(currtime, 8, Qt::AlignRight);
        customPlot->replot();

        // calculate frames per second:
        static double lastFpsKey;
        static int frameCount;
        ++frameCount;
        if (currtime-lastFpsKey > 2) // average fps over 2 seconds
        {
          lastFpsKey = currtime;
          frameCount = 0;
        }
    });
}

void CatLineChart::StartTimer(bool start)
{
    if(start)
    {
        ui->StartButton->setText("Stop");
    } else {
        ui->StartButton->setText("Start");
    }
}

void CatLineChart::UpdateGraphScatterStyle(int id)
{
    for(auto temp : m_pGraphs)
    {
        temp->setScatterStyle(QCPScatterStyle(
                                  (QCPScatterStyle::ScatterShape)id, 5));
    }
    ui->ChartWidget->replot();
}

void CatLineChart::UpdateGraphLineStyle(int id)
{
    for(auto temp : m_pGraphs)
    {
        temp->setLineStyle((QCPGraph::LineStyle)id);
    }
    ui->ChartWidget->replot();
}

void CatLineChart::On_UpdateDxva(QString dxva)
{
    if(dxva == "Not")
    {
        ui->ChartWidget->setOpenGl(false);
    } else if(dxva == "OpenGL") {
        ui->ChartWidget->setOpenGl(true);
    }
    ui->ChartWidget->replot();
}

void CatLineChart::On_MousePress()
{
    //如果一个轴被选中，只允许该轴的方向被拖动
    //如果没有选择轴，两个方向都可以拖动
    QCustomPlot *customPlot = ui->ChartWidget;
    if (customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
        customPlot->axisRect()->setRangeDrag(customPlot->xAxis->orientation());
    else if (customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
        customPlot->axisRect()->setRangeDrag(customPlot->yAxis->orientation());
    else
        customPlot->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
}

void CatLineChart::hideEvent(QHideEvent *event)
{
    Q_UNUSED(event)

    if(m_pDataTimer->isActive())
    {
        ui->StartButton->click();
    }
}
