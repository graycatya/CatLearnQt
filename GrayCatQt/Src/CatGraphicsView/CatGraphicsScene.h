#ifndef CATGRAPHICSSCENE_H
#define CATGRAPHICSSCENE_H

#include <QGraphicsScene>

class CatGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit CatGraphicsScene(QObject *parent = nullptr);
    ~CatGraphicsScene();

private:
};

#endif // CATGRAPHICSSCENE_H
