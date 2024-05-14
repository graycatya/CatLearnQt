#ifndef CATBARCHART_H
#define CATBARCHART_H

#include <QWidget>
#include <QMap>

class QCPBars;
class QCPAxisRect;
class CatCustomChart;
class ListiongOptions;

namespace Ui {
class CatBarChart;
}

class CatBarChart : public QWidget
{
    Q_OBJECT

public:
    explicit CatBarChart(QWidget *parent = nullptr);
    ~CatBarChart();

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
    void On_MousePress();
    void On_UpdateWidthType(int id);
    void On_BarCheck(int bar, bool state);

protected:
    void hideEvent(QHideEvent *event) override;
    void showEvent(QShowEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;


private:
    Ui::CatBarChart *ui;
    QVector<CatCustomChart*> m_pCatCustomCharts;
    QVector<QCPBars*> m_pBars;
    ListiongOptions *m_pListiongOptions;
    QTimer *m_pDataTimer;
};

#endif // CATBARCHART_H
