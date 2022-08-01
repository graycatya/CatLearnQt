#include "CatBarChart.h"
#include "ui_CatBarChart.h"

#include "../../CatConfig/CatConfig.h"

#include <CatLog>

#include "CatControl/ListingOptions.h"
#include "CatWidget/CatQcustomplot/CatQcustomplotCharts/CatCustomChart.h"
#include "CatWidget/CatQcustomplot/CatBars.h"

#if (QT_VERSION >= QT_VERSION_CHECK(5,10,0))
#include <QRandomGenerator>
#endif

CatBarChart::CatBarChart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CatBarChart),
    m_pDataTimer(nullptr)
{
    ui->setupUi(this);
    InitUi();
    InitProperty();
    InitConnect();
    InitChartConnect();
}

CatBarChart::~CatBarChart()
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

void CatBarChart::InitUi()
{
    ui->RootLayout->setStretchFactor(ui->FunctionWidget, 1);
    ui->RootLayout->setStretchFactor(ui->ChartWidgets, 9);

    m_pListiongOptions = new ListiongOptions(ListiongOptions::VBox, ui->ChartWidgets);
    m_pListiongOptions->RemoveBackGaugeItem();
    ui->ChartWidgetsLayout->addWidget(m_pListiongOptions);

    ui->WidthTypeBox->addItems(CatQcustomplot::BarsWidthType());
    QListView *view_0 = new QListView();
    view_0->setObjectName("StyleComboBoxView");
    ui->WidthTypeBox->setView(view_0);
    ui->WidthTypeBox->setCurrentText("wtAbsolute");
    StartTimer(false);

    ui->Bar_0->setChecked(true);
    ui->Bar_1->setChecked(true);
    ui->Bar_2->setChecked(true);
    ui->Bar_3->setChecked(true);
}

void CatBarChart::InitProperty()
{
    m_pDataTimer = new QTimer(this);
    UpdateStyle();
    InitCharts();
}

void CatBarChart::InitConnect()
{
    connect(CatConfig::Instance(), &CatConfig::UpdateStyleSheets, this, [=](){
        UpdateStyle();
    });

    connect(ui->StartButton, &QPushButton::clicked, this, [=](){
        if(m_pDataTimer->isActive())
        {
            m_pDataTimer->stop();
            StartTimer(false);
            for(auto temp : m_pCatCustomCharts)
            {
                temp->setInteractions(QCP::iRangeDrag | QCP::iSelectAxes
                                      | QCP::iSelectLegend | QCP::iSelectPlottables);
            }
        } else {
            m_pDataTimer->start(500);
            StartTimer(true);
            for(auto temp : m_pCatCustomCharts)
            {
                temp->setInteractions(QCP::iSelectAxes |
                                             QCP::iSelectLegend | QCP::iSelectPlottables );
            }
        }
    });
}

void CatBarChart::UpdateStyle()
{
    QString stylePath;
    if(CatConfig::ConfigExist())
    {
        stylePath = ":/qss/" + CatConfig::GetValue("style", "Defaule").toString() + "/";
    } else {
        stylePath = ":/qss/CatGray/";
    }

    QFile file_0(stylePath + "CatBarChart.css");
    file_0.open(QIODevice::ReadOnly);
    QString stylehoot_0 = QLatin1String(file_0.readAll());
    this->setStyleSheet(stylehoot_0);
    file_0.close();
}

void CatBarChart::InitCharts()
{
    for(int i = 0; i < 4; i++)
    {
        CatCustomChart *customPlot = new CatCustomChart(ui->ChartWidgets);
        customPlot->legend->setVisible(true);
        customPlot->legend->setSelectedIconBorderPen(QPen(Qt::gray));
        customPlot->SetGraphSelectionDecoratorWidth(3);
        customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop | Qt::AlignLeft);
        QColor color = QColor(qSin(i * 1 + 1.2) * 80 + 80, qSin(i*0.3 + 0) * 80 + 80, qSin(i*0.3 + 1.5) * 80 + 80);
        QPen pen;
        pen.setWidth(3);
        pen.setColor(color);
        int width = 10;
        QCPBars *bar = customPlot->AddBars(width, pen, color, QString("Bar %1").arg(QString::number(i)));
        m_pBars.push_back(bar);
        QSharedPointer<QCPAxisTickerDateTime> timeTicker(new QCPAxisTickerDateTime);
        timeTicker->setDateTimeFormat("yyyy-MM-dd hh:mm:ss");
        customPlot->xAxis->setTicker(timeTicker);

        customPlot->axisRect()->setupFullAxesBox();
        customPlot->yAxis->setRange(0.0, 140.0);

        m_pListiongOptions->AddWidget(customPlot);
        m_pCatCustomCharts.push_back(customPlot);
    }

    //m_pCatCustomCharts.at(1)->setVisible(false);
}

void CatBarChart::InitChartConnect()
{
    for(auto temp : m_pCatCustomCharts)
    {
        CatCustomChart *customPlot = temp;
        connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
        connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
        connect(ui->WidthTypeBox, SIGNAL(currentIndexChanged(int)), this, SLOT(On_UpdateWidthType(int)));
        connect(customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(On_MousePress()));

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
        });

        connect(customPlot, &CatCustomChart::mouseMove, this, [=](QMouseEvent* event){
            CatCustomChart *customPot = qobject_cast<CatCustomChart*>(sender());
            //获取鼠标坐标
            QVector<CatBarsRectData> rectdatas = dynamic_cast<CatBars*>(customPot->GetBars().at(0))->CurrentShowRectDatass();
            QToolTip::hideText();
            for(auto temp : rectdatas)
            {
                if(temp.rect.contains(event->pos()))
                {
                    QDateTime time;
                    time.setSecsSinceEpoch(temp.key);
                    QString key = time.toString("yyyy-MM-dd hh:mm:ss");
                    QString value = QString("%1").arg(QString::number(temp.value, 'f', 2));
                    QString str = value + "\n" + key;
                    QToolTip::showText(event->globalPos(), str, customPot);
                }
            }
        });
    }
    // 定时更新动态数据
    connect(m_pDataTimer, &QTimer::timeout, this, [=](){
#if (QT_VERSION < QT_VERSION_CHECK(5,10,0))
        double currtime = (double)(QDateTime::currentMSecsSinceEpoch()) / 1000.0;
        qsrand(currtime);

        static double lastPointKey = 0;
        if (currtime-lastPointKey > 0.5) // at most add point every 2 ms
        {
          // add data to lines:
          for(auto temp : m_pBars)
          {
              int value = qrand() % 100;
              temp->addData(currtime, value);
              QDateTime time;
              time.setSecsSinceEpoch(currtime);
          }
          lastPointKey = currtime;
        }
#else
        double currtime = (double)(QDateTime::currentMSecsSinceEpoch()) / 1000.0;

        QRandomGenerator prng1(currtime);
        static double lastPointKey = 0;
        if (currtime-lastPointKey > 0.5) // at most add point every 2 ms
        {
          // add data to lines:
          for(auto temp : m_pBars)
          {
              int value = prng1.generate() % 100;
              temp->addData(currtime, value);
              QDateTime time;
              time.setSecsSinceEpoch(currtime);
          }
          lastPointKey = currtime;
        }
#endif
        // make key axis range scroll with the data (at a constant range size of 8):
        for(auto customPlot : m_pCatCustomCharts)
        {
            customPlot->xAxis->setRange(currtime, 8, Qt::AlignRight);
            customPlot->replot();
        }

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


    connect(ui->Bar_0, &QCheckBox::stateChanged, this, [=](int state){
        if(state == 2)
        {
            On_BarCheck(0, true);
        } else {
            On_BarCheck(0, false);
        }
    });

    connect(ui->Bar_1, &QCheckBox::stateChanged, this, [=](int state){
        if(state == 2)
        {
            On_BarCheck(1, true);
        } else {
            On_BarCheck(1, false);
        }
    });

    connect(ui->Bar_2, &QCheckBox::stateChanged, this, [=](int state){
        if(state == 2)
        {
            On_BarCheck(2, true);
        } else {
            On_BarCheck(2, false);
        }
    });

    connect(ui->Bar_3, &QCheckBox::stateChanged, this, [=](int state){
        if(state == 2)
        {
            On_BarCheck(3, true);
        } else {
            On_BarCheck(3, false);
        }
    });
}

void CatBarChart::StartTimer(bool start)
{
    if(start)
    {
        ui->StartButton->setText("Stop");
        for(auto temp : m_pCatCustomCharts)
        {
            temp->SetTracer(false);
        }
    } else {
        ui->StartButton->setText("Start");
        for(auto temp : m_pCatCustomCharts)
        {
            temp->SetTracer(true);
        }
    }
}

void CatBarChart::On_MousePress()
{
    //如果一个轴被选中，只允许该轴的方向被拖动
    //如果没有选择轴，两个方向都可以拖动
    for(auto temp : m_pCatCustomCharts)
    {
        QCustomPlot *customPlot = temp;
        customPlot->axisRect()->setRangeDrag(customPlot->xAxis->orientation());
    }
}

void CatBarChart::On_UpdateWidthType(int id)
{
    for(auto temp : m_pBars)
    {
        temp->setWidthType((QCPBars::WidthType)id);
    }
    for(auto temp : m_pCatCustomCharts)
    {
        temp->replot();
    }
}

void CatBarChart::On_BarCheck(int bar, bool state)
{
    m_pCatCustomCharts.at(bar)->setVisible(state);
}

void CatBarChart::hideEvent(QHideEvent *event)
{
    Q_UNUSED(event)
    if(m_pDataTimer->isActive())
    {
        ui->StartButton->click();
    }
}

void CatBarChart::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
    for(auto temp : m_pCatCustomCharts)
    {
        temp->replot();
    }
}

void CatBarChart::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
}
