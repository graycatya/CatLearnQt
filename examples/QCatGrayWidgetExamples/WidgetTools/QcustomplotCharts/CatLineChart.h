#ifndef CATLINECHART_H
#define CATLINECHART_H

#include <QWidget>
#include <QDateTime>

class QCPGraph;
class QComboBox;
class QCPLayoutElement;

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
    void UpdateTracerStyle(int id);
    void UpdatePositionType(int id);
    void On_UpdateDxva(QString dxva);
    void On_MousePress();
    void On_LineCheck(int line, bool state);

    void on_SaveButton_clicked();

protected:
    void hideEvent(QHideEvent *event) override;
    void showEvent(QShowEvent *event) override;

private:
    Ui::CatLineChart *ui;
    QVector<QCPGraph*> m_pGraphs;
    QTimer *m_pDataTimer;
    QComboBox *m_pDxvaBox;
    QDateTime m_pStartTime;
    QDateTime m_pStopTime;
    bool m_bFirstStart;

    double m_nDataSize;
};

#endif // CATLINECHART_H
