#ifndef CATGRAPHICSVIEW_H
#define CATGRAPHICSVIEW_H

#include <QGraphicsView>

class CatGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit CatGraphicsView(QWidget *parent = nullptr);
    ~CatGraphicsView();

private:

};

#endif // CATGRAPHICSVIEW_H
