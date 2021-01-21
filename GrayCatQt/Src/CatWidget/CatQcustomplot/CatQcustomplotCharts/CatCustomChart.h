#ifndef CATQCLINECHART_H
#define CATQCLINECHART_H

#include "../CatQcustomplot.h"

class CatCustomChart : public CatQcustomplot
{
    Q_OBJECT
    Q_PROPERTY(QPen TracerPen READ GetTracerPen WRITE SetTracerPen)
    Q_PROPERTY(int TracerPenWidth READ GetTracerPenWidth WRITE SetTracerPenWidth)
    Q_PROPERTY(QColor TracerPenColor READ GetTracerPenColor WRITE SetTracerPenColor)

    Q_PROPERTY(QPen TracerXTextPen READ GetTracerXTextPen WRITE SetTracerXTextPen)
    Q_PROPERTY(int TracerXTextPenWidth READ GetTracerXTextPenWidth WRITE SetTracerXTextPenWidth)
    Q_PROPERTY(QColor TracerXTextPenColor READ GetTracerXTextPenColor WRITE SetTracerXTextPenColor)

    Q_PROPERTY(QColor TracerXTextColor READ GetTracerXTextColor WRITE SetTracerXTextColor)
    Q_PROPERTY(QColor TracerXTextBackgroundColor READ GetTracerXTextBackgroundColor WRITE SetTracerXTextBackgroundColor)

    Q_PROPERTY(QPen TracerYTextPen READ GetTracerYTextPen WRITE SetTracerYTextPen)
    Q_PROPERTY(int TracerYTextPenWidth READ GetTracerYTextPenWidth WRITE SetTracerYTextPenWidth)
    Q_PROPERTY(QColor TracerYTextPenColor READ GetTracerYTextPenColor WRITE SetTracerYTextPenColor)

    Q_PROPERTY(QColor TracerYTextColor READ GetTracerYTextColor WRITE SetTracerYTextColor)
    Q_PROPERTY(QColor TracerYTextBackgroundColor READ GetTracerYTextBackgroundColor WRITE SetTracerYTextBackgroundColor)

public:
    explicit CatCustomChart(QWidget *parent = nullptr);
    ~CatCustomChart();

    // 游标
    void SetTracer(bool tracer);
    bool Tracer( void ) const { return m_bTracer; }

    void SetSelectTraceGraph(QCPGraph * graph);

    QPen GetTracerPen() { return m_pTracer->pen(); }
    int GetTracerPenWidth() { return m_pTracer->pen().width(); }
    QColor GetTracerPenColor() { return m_pTracer->pen().color(); }

    QPen GetTracerXTextPen() { return m_pTracerXText->pen(); }
    int GetTracerXTextPenWidth() { return m_pTracerXText->pen().width(); }
    QColor GetTracerXTextPenColor() { return m_pTracerXText->pen().color(); }

    QColor GetTracerXTextColor() { return m_pTracerXText->color(); }
    QColor GetTracerXTextBackgroundColor() { return m_pTracerXText->backgroundColor(); }

    QPen GetTracerYTextPen() { return m_pTracerYText->pen(); }
    int GetTracerYTextPenWidth() { return m_pTracerYText->pen().width(); }
    QColor GetTracerYTextPenColor() { return m_pTracerYText->pen().color(); }

    QColor GetTracerYTextColor() { return m_pTracerYText->color(); }
    QColor GetTracerYTextBackgroundColor() { return m_pTracerYText->backgroundColor(); }

private:
    void InitUi();
    void InitProperty();


protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void showEvent(QShowEvent *event) override;

public slots:
    void SetTracerPen(QPen pen);
    void SetTracerPenStyle(Qt::PenStyle style);
    void SetTracerPenWidth(int width);
    void SetTracerPenColor(QColor color);
    void SetTracerStyle(QCPItemTracer::TracerStyle style);

    void SetTracerXTextPen(QPen pen);
    void SetTracerXTextPenWidth(int width);
    void SetTracerXTextPenColor(QColor color);

    void SetTracerXTextColor(QColor color);
    void SetTracerXTextBackgroundColor(QColor color);
    void SetTracerXPositionType(QCPItemPosition::PositionType type);

    void SetTracerYTextPen(QPen pen);
    void SetTracerYTextPenWidth(int width);
    void SetTracerYTextPenColor(QColor color);

    void SetTracerYTextColor(QColor color);
    void SetTracerYTextBackgroundColor(QColor color);
    void SetTracerYPositionType(QCPItemPosition::PositionType type);



private:
    bool m_bTracer; // x,y轴游标

    QCPItemTracer *m_pTracer;   // 游标
    QCPGraph *m_pTraceGraph;    // 需要使用的游标项
    QCPItemText *m_pTracerXText;    // 游标 x 值
    QCPItemText *m_pTracerYText;    // 游标 y 值
};

#endif // CATQCLINECHART_H
