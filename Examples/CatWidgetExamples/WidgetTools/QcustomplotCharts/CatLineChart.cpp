#include "CatLineChart.h"
#include "ui_CatLineChart.h"

#include "../../CatConfig/CatConfig.h"
#include <CatUniversal/CatFile.h>
#include <CatLog>
#include <QFileDialog>

CatLineChart::CatLineChart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CatLineChart),
    m_pDataTimer(new QTimer(this)),
    m_bFirstStart(true),
    m_nDataSize(0)
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

    QListView *view_3 = new QListView();
    view_3->setObjectName("StyleComboBoxView");
    ui->TracerStyleBox->setView(view_3);
    ui->TracerStyleBox->addItems(ui->ChartWidget->TracerStyleList());

    QListView *view_4 = new QListView();
    view_4->setObjectName("StyleComboBoxView");
    ui->PositionTypeBox->setView(view_4);
    ui->PositionTypeBox->addItems(ui->ChartWidget->PositionTypeList());


    // 支持opengl
    QLabel *m_pDXVALabel = new QLabel(ui->FunctionWidget);
    m_pDXVALabel->setObjectName(QString::fromUtf8("DxvaLabel"));
    ui->formLayout->setWidget(ui->formLayout->rowCount() + 1, QFormLayout::LabelRole, m_pDXVALabel);

    m_pDXVALabel->setText(QCoreApplication::translate("CatLineChart", "DxVa:", nullptr));

    m_pDxvaBox = new QComboBox(ui->FunctionWidget);
    m_pDxvaBox->setObjectName(QString::fromUtf8("DxvaBox"));
    ui->formLayout->setWidget(ui->formLayout->rowCount() - 1, QFormLayout::FieldRole, m_pDxvaBox);

    QListView *view_2 = new QListView();
    view_2->setObjectName("StyleComboBoxView");
    m_pDxvaBox->setView(view_2);

    m_pDxvaBox->addItems({"Not", "OpenGL"});

    StartTimer(false);

    ui->Line_0->setChecked(true);
    ui->Line_1->setChecked(true);
    ui->Line_2->setChecked(true);
    ui->Line_3->setChecked(true);
    ui->SaveButton->setVisible(false);
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
            m_pDataTimer->start(500);
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
    } else {
        stylePath = ":/qss/CatGray/";
    }

    QFile file_0(stylePath + "CatLineChart.css");
    file_0.open(QIODevice::ReadOnly);
    QString stylehoot_0 = QLatin1String(file_0.readAll());
    this->setStyleSheet(stylehoot_0);
    file_0.close();
}

void CatLineChart::InitCharts()
{
    CatCustomChart *customPlot = ui->ChartWidget;
    customPlot->legend->setVisible(true);
    customPlot->legend->setSelectedIconBorderPen(QPen(Qt::gray));
    customPlot->SetGraphSelectionDecoratorWidth(3);
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop | Qt::AlignLeft);
    //customPlot->SetTracerPenStyle(Qt::DashLine);
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
    CatCustomChart *customPlot = ui->ChartWidget;
    connect(ui->ScatterShapeBox, SIGNAL(currentIndexChanged(int)), this, SLOT(UpdateGraphScatterStyle(int)));
    connect(ui->LineStyleBox, SIGNAL(currentIndexChanged(int)), this, SLOT(UpdateGraphLineStyle(int)));
    connect(ui->TracerStyleBox, SIGNAL(currentIndexChanged(int)), this, SLOT(UpdateTracerStyle(int)));
    connect(ui->PositionTypeBox, SIGNAL(currentIndexChanged(int)), this, SLOT(UpdatePositionType(int)));
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
            if(graph->visible())
            {
                QCPPlottableLegendItem *item = customPlot->legend->itemWithPlottable(graph);
                if (item->selected() || graph->selected())//选中了哪条曲线或者曲线的图例
                {
                    customPlot->SetSelectTraceGraph(graph);
                    graph->selectionDecorator()->setPen(ui->ChartWidget->GetGraphSelectionDecoratorPen());
                    item->setSelected(true);//同时选中曲线和图例
                    graph->setSelection(QCPDataSelection(graph->data()->dataRange()));
                }
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
        //m_nDataSize++;
    });

    connect(ui->Line_0, &QCheckBox::stateChanged, this, [=](int state){
        if(state == 2)
        {
            On_LineCheck(0, true);
        } else {
            On_LineCheck(0, false);
        }
    });

    connect(ui->Line_1, &QCheckBox::stateChanged, this, [=](int state){
        if(state == 2)
        {
            On_LineCheck(1, true);
        } else {
            On_LineCheck(1, false);
        }
    });

    connect(ui->Line_2, &QCheckBox::stateChanged, this, [=](int state){
        if(state == 2)
        {
            On_LineCheck(2, true);
        } else {
            On_LineCheck(2, false);
        }
    });

    connect(ui->Line_3, &QCheckBox::stateChanged, this, [=](int state){
        if(state == 2)
        {
            On_LineCheck(3, true);
        } else {
            On_LineCheck(3, false);
        }
    });
}

void CatLineChart::StartTimer(bool start)
{
    if(start)
    {
        ui->StartButton->setText("Stop");
        ui->ChartWidget->SetTracer(false);
        ui->SaveButton->setVisible(false);
        if(m_bFirstStart)
        {
            m_pStartTime = QDateTime::currentDateTime();
        }
        m_bFirstStart = false;
    } else {
        ui->StartButton->setText("Start");
        ui->ChartWidget->SetTracer(true);
        ui->SaveButton->setVisible(true);
        m_pStopTime = QDateTime::currentDateTime();
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

void CatLineChart::UpdateTracerStyle(int id)
{
    ui->ChartWidget->SetTracerStyle((QCPItemTracer::TracerStyle)id);
}

void CatLineChart::UpdatePositionType(int id)
{
    ui->ChartWidget->SetTracerXPositionType((QCPItemPosition::PositionType)id);
    ui->ChartWidget->SetTracerYPositionType((QCPItemPosition::PositionType)id);
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

void CatLineChart::On_LineCheck(int line, bool state)
{
    QCustomPlot *customPlot = ui->ChartWidget;
    m_pGraphs.at(line)->setVisible(state);

    for(int i = 0; i < m_pGraphs.size(); i++)
    {
        m_pGraphs.at(i)->removeFromLegend(customPlot->legend);
    }

    bool showlegend = false;

    for(int i = 0; i < m_pGraphs.size(); i++)
    {
        if(m_pGraphs.at(i)->visible())
        {
            showlegend = true;
            m_pGraphs.at(i)->addToLegend(customPlot->legend);
        }
    }

    customPlot->legend->setVisible(showlegend);
    ui->ChartWidget->replot();
}

void CatLineChart::hideEvent(QHideEvent *event)
{
    Q_UNUSED(event)

    if(m_pDataTimer->isActive())
    {
        ui->StartButton->click();
    }
}

void CatLineChart::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
    ui->ChartWidget->replot();
}

void CatLineChart::on_SaveButton_clicked()
{
    QCustomPlot *customPlot = ui->ChartWidget;

    QDateTime lastxlower;
    lastxlower.setSecsSinceEpoch(customPlot->xAxis->range().lower);
    QDateTime lastxupper;
    lastxupper.setSecsSinceEpoch(customPlot->xAxis->range().upper);
    double lastylower = customPlot->yAxis->range().lower;
    double lastyupper = customPlot->yAxis->range().upper;
    QString filename = QDateTime::currentDateTime().toString("yyMMddhhmmss") + ".png";
    CatFile::Existe(CatConfig::GetValue("SaveFilePath").toString(), true);
    QString definepath = CatConfig::GetValue("SaveFilePath").toString() + "/" + filename;

    QString file = QFileDialog::getSaveFileName(this, tr("Save file"), definepath, "png(*.png)");
    if(!file.isEmpty())
    {
        m_nDataSize = static_cast<double>(m_pStartTime.secsTo(m_pStopTime));
        customPlot->xAxis->setRange((double)(m_pStopTime.toMSecsSinceEpoch()) / 1000.0, m_nDataSize, Qt::AlignRight);
        customPlot->yAxis->setRange(0.0, 100.0);
        ui->ChartWidget->SetTracer(false);
        customPlot->replot();
        customPlot->toPixmap(customPlot->width(), customPlot->height()).save(file);
        qDebug() << file;
        customPlot->xAxis->setRange(lastxlower.toTime_t(), lastxupper.toTime_t());
        customPlot->yAxis->setRange(lastylower, lastyupper);
        ui->ChartWidget->SetTracer(true);
        customPlot->replot();
    }


}
