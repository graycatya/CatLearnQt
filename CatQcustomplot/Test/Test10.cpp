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

}

void Test10::InitProperty()
{
    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                          QCP::iSelectLegend | QCP::iSelectPlottables);
    ui->widget->setOpenGl(true);
    dataTimer = new QTimer(this);
    QCustomPlot *customPlot = ui->widget;
    customPlot->addGraph(); // blue line
    customPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    customPlot->addGraph(); // red line
    customPlot->graph(1)->setPen(QPen(QColor(255, 110, 40)));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
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
        double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
        static double lastPointKey = 0;
        if (key-lastPointKey > 0.002) // at most add point every 2 ms
        {
          // add data to lines:
          customPlot->graph(0)->addData(key, qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843));
          customPlot->graph(1)->addData(key, qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364));
          // rescale value (vertical) axis to fit the current data:
          //ui->customPlot->graph(0)->rescaleValueAxis();
          //ui->customPlot->graph(1)->rescaleValueAxis(true);
          lastPointKey = key;
        }
        // make key axis range scroll with the data (at a constant range size of 8):
        customPlot->xAxis->setRange(key, 8, Qt::AlignRight);
        customPlot->replot();

        // calculate frames per second:
        static double lastFpsKey;
        static int frameCount;
        ++frameCount;
        if (key-lastFpsKey > 2) // average fps over 2 seconds
        {
          /*statusBar->showMessage(
                QString("%1 FPS, Total Data points: %2")
                .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
                .arg(customPlot->graph(0)->data()->size()+customPlot->graph(1)->data()->size())
                , 0);*/
          lastFpsKey = key;
          frameCount = 0;
        }
    });
    //dataTimer->start(0); // Interval 0 means to refresh as fast as possible
}

void Test10::on_pushButton_clicked()
{
    if(dataTimer->isActive())
    {
        dataTimer->stop();
    } else {
        dataTimer->start(0);
    }
}
