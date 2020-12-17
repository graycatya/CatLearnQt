#include "Test10.h"
#include "ui_Test10.h"

Test10::Test10(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Test10)
{
    ui->setupUi(this);
    InitUi();
    InitProperty();
}

Test10::~Test10()
{
    delete ui;
}

void Test10::InitUi()
{
    pen.setWidth(1);
    pen.setColor(QColor(0,0,255));
}

void Test10::InitProperty()
{
    /*ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                          QCP::iSelectLegend | QCP::iSelectPlottables);*/
    //ui->widget->setOpenGl(true);

    dataTimer = new QTimer(this);

    QCustomPlot *customPlot = ui->widget;
    customPlot->legend->setVisible(true);
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop | Qt::AlignHCenter);
    customPlot->setNoAntialiasingOnDrag(true);//禁用抗锯齿，以提高性能
    customPlot->addGraph(); // blue line
    customPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    customPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);
    customPlot->graph(0)->setName("test");
    customPlot->addGraph(); // red line
    customPlot->graph(1)->setPen(QPen(QColor(255, 110, 40)));
    customPlot->graph(1)->setScatterStyle(QCPScatterStyle::ssDisc);

    QSharedPointer<QCPAxisTickerDateTime> timeTicker(new QCPAxisTickerDateTime);
    timeTicker->setDateTimeFormat("yyyy-MM-dd hh:mm:ss");
    customPlot->xAxis->setTicker(timeTicker);
    customPlot->axisRect()->setupFullAxesBox();
    customPlot->yAxis->setRange(-1.2, 1.2);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    connect(dataTimer, &QTimer::timeout, this, [=](){
        static QTime time(QTime::currentTime());
        // calculate two new data points:
        //double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds

        double currtime = (double)(QDateTime::currentMSecsSinceEpoch()) / 1000.0;
        static double lastPointKey = 0;
        if (currtime-lastPointKey > 0.5) // at most add point every 2 ms
        {
          // add data to lines:
          customPlot->graph(0)->addData(currtime, qSin(currtime)+qrand()/(double)RAND_MAX*1*qSin(currtime/0.3843));
          customPlot->graph(1)->addData(currtime, qCos(currtime)+qrand()/(double)RAND_MAX*0.5*qSin(currtime/0.4364));
          // rescale value (vertical) axis to fit the current data:
          //ui->customPlot->graph(0)->rescaleValueAxis();
          //ui->customPlot->graph(1)->rescaleValueAxis(true);
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
          /*statusBar->showMessage(
                QString("%1 FPS, Total Data points: %2")
                .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
                .arg(customPlot->graph(0)->data()->size()+customPlot->graph(1)->data()->size())
                , 0);
            */
          lastFpsKey = currtime;
          frameCount = 0;
        }
    });
    //dataTimer->start(0); // Interval 0 means to refresh as fast as possible

    // 用户更改QCustomPlot中的选择后（例如通过单击），将发出此信号。
    connect(customPlot, &QCustomPlot::selectionChangedByUser, this, [=](){
        for (int i = 0; i < customPlot->graphCount(); ++i)
        {
            QCPGraph *graph = customPlot->graph(i);

            QCPPlottableLegendItem *item = customPlot->legend->itemWithPlottable(graph);
            if (item->selected() || graph->selected())//选中了哪条曲线或者曲线的图例
            {
                graph->selectionDecorator()->setPen(pen);
                item->setSelected(true);//同时选中曲线和图例
                graph->setSelection(QCPDataSelection(graph->data()->dataRange()));
                //traceGraph = graph;
            }
        }

    });
}

void Test10::on_pushButton_clicked()
{
    if(dataTimer->isActive())
    {
        dataTimer->stop();
        ui->widget->graph(1)->setVisible(true);
        ui->widget->legend->item(1)->setVisible(true);
        ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                              QCP::iSelectLegend | QCP::iSelectPlottables);
        ui->widget->replot();
    } else {
        ui->widget->graph(1)->setVisible(false);
        ui->widget->legend->item(1)->setVisible(false);
        ui->widget->update();
        ui->widget->setInteractions(QCP::iRangeZoom | QCP::iSelectAxes | QCP::iSelectLegend | QCP::iSelectPlottables );
        dataTimer->start(0);
        ui->widget->show();
        ui->widget->replot();
    }
}
