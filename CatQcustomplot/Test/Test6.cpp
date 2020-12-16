#include "Test6.h"
#include "ui_Test6.h"

Test6::Test6(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Test6)
{
    ui->setupUi(this);
    InitUi();
    InitProperty();
}

Test6::~Test6()
{
    delete ui;
}

void Test6::InitUi()
{

}

void Test6::InitProperty()
{
    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                          QCP::iSelectLegend | QCP::iSelectPlottables);
    QCustomPlot *customPlot = ui->widget;
    customPlot->legend->setVisible(true);
    customPlot->legend->setFont(QFont("Helvetica", 9));
    customPlot->legend->setRowSpacing(-3);
    QVector<QCPScatterStyle::ScatterShape> shapes;
    shapes << QCPScatterStyle::ssNone;
    shapes << QCPScatterStyle::ssDot;
    shapes << QCPScatterStyle::ssCross;
    shapes << QCPScatterStyle::ssPlus;
    shapes << QCPScatterStyle::ssCircle;
    shapes << QCPScatterStyle::ssDisc;
    shapes << QCPScatterStyle::ssSquare;
    shapes << QCPScatterStyle::ssDiamond;
    shapes << QCPScatterStyle::ssStar;
    shapes << QCPScatterStyle::ssTriangle;
    shapes << QCPScatterStyle::ssTriangleInverted;
    shapes << QCPScatterStyle::ssCrossSquare;
    shapes << QCPScatterStyle::ssPlusSquare;
    shapes << QCPScatterStyle::ssCrossCircle;
    shapes << QCPScatterStyle::ssPlusCircle;
    shapes << QCPScatterStyle::ssPeace;
    shapes << QCPScatterStyle::ssCustom;

    QPen pen;
    // add graphs with different scatter styles:
    for (int i=0; i<shapes.size(); ++i)
    {
      customPlot->addGraph();
      pen.setColor(QColor(qSin(i*0.3)*100+100, qSin(i*0.6+0.7)*100+100, qSin(i*0.4+0.6)*100+100));
      // generate data:
      QVector<double> x(10), y(10);
      for (int k=0; k<10; ++k)
      {
        x[k] = k/10.0 * 4*3.14 + 0.01;
        y[k] = 7*qSin(x[k])/x[k] + (shapes.size()-i)*5;
      }
      customPlot->graph()->setData(x, y);
      customPlot->graph()->rescaleAxes(true);
      customPlot->graph()->setPen(pen);
      customPlot->graph()->setName(QCPScatterStyle::staticMetaObject.enumerator(QCPScatterStyle::staticMetaObject.indexOfEnumerator("ScatterShape")).valueToKey(shapes.at(i)));
      customPlot->graph()->setLineStyle(QCPGraph::lsLine);
      // set scatter style:
      if (shapes.at(i) != QCPScatterStyle::ssCustom)
      {
        customPlot->graph()->setScatterStyle(QCPScatterStyle(shapes.at(i), 10));
      }
      else
      {
        QPainterPath customScatterPath;
        for (int i=0; i<3; ++i)
          customScatterPath.cubicTo(qCos(2*M_PI*i/3.0)*9, qSin(2*M_PI*i/3.0)*9, qCos(2*M_PI*(i+0.9)/3.0)*9, qSin(2*M_PI*(i+0.9)/3.0)*9, 0, 0);
        customPlot->graph()->setScatterStyle(QCPScatterStyle(customScatterPath, QPen(Qt::black, 0), QColor(40, 70, 255, 50), 10));
      }
    }
    // set blank axis lines:
    customPlot->rescaleAxes();
    customPlot->xAxis->setTicks(false);
    customPlot->yAxis->setTicks(false);
    customPlot->xAxis->setTickLabels(false);
    customPlot->yAxis->setTickLabels(false);
    // make top right axes clones of bottom left axes:
    customPlot->axisRect()->setupFullAxesBox();
}
