#ifndef CATGRAPHICSVIEW_H
#define CATGRAPHICSVIEW_H

#include <QGraphicsView>

class CatGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit CatGraphicsView(QWidget *parent = nullptr);
    ~CatGraphicsView();

    void ScaleZoomIn();
    void ScaleZoomOut();
    void Reset();

private:
    void InitProperty();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    QPoint lastPoint;
    QPoint endPoint;
    bool m_bPress;

};

#endif // CATGRAPHICSVIEW_H
