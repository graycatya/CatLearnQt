#ifndef CATGRAPHICSSCENE_H
#define CATGRAPHICSSCENE_H

#include <QGraphicsScene>

class CatGraphicsView;
class TeachingToolCompass;
class TeachingToolProtractor;
class TeachingToolRuler;
class TeachingToolTrangle;

class CatGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit CatGraphicsScene(QObject *parent = nullptr);
    ~CatGraphicsScene();

    void SetView(CatGraphicsView *view);
    CatGraphicsView *View( void );


    void AddTeachingToolProtractor();
    void AddTeachingToolRuler();
    void AddTeachingToolTrangle();
    void AddTeachingToolCompass();



private:
    CatGraphicsView *m_yView;

};

#endif // CATGRAPHICSSCENE_H
