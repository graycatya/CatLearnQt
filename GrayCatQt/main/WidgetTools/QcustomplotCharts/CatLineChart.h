#ifndef CATLINECHART_H
#define CATLINECHART_H

#include <QWidget>

class QCPGraph;

namespace Ui {
class CatLineChart;
}

class CatLineChart : public QWidget
{
    Q_OBJECT

public:
    explicit CatLineChart(QWidget *parent = nullptr);
    ~CatLineChart();

private:
    void InitUi();
    void InitProperty();
    void InitConnect();

    void UpdateStyle();

    //图表设置
    void InitCharts();
    void InitChartConnect();

private slots:
    void StartTimer(bool);
    void UpdateGraphScatterStyle(int id);
    void UpdateGraphLineStyle(int id);

private:
    Ui::CatLineChart *ui;
    QVector<QCPGraph*> m_pGraphs;
    QTimer *m_pDataTimer;
};

#endif // CATLINECHART_H
