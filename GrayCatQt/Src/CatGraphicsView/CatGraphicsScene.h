#ifndef CATGRAPHICSSCENE_H
#define CATGRAPHICSSCENE_H

#include <QGraphicsScene>

#include "CatGraphicsObject.h"

class CatGraphicsView;
class TeachingToolCompass;
class TeachingToolProtractor;
class TeachingToolRuler;
class TeachingToolTrangle;

class CatGraphicPen;

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
    void InitProperty();

protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

public slots:
    void On_DrawingBoard_SelectState();
    void On_DrawingBoard_PenState();

private:
    CatGraphicsView *m_yView;
    QVector<TeachingToolCompass*> m_pTeachingToolCompass;
    QVector<TeachingToolProtractor*> m_pTeachingToolProtractor;
    QVector<TeachingToolRuler*> m_pTeachingToolRuler;
    QVector<TeachingToolTrangle*> m_pTeachingToolTrangle;
    QList<CatGraphicPen*> m_PCatGraphicPens;
    //QPointF lastpoint,endpoint; //存储鼠标的按下和放开时的坐标
    bool m_bpen;

    CatGraphicsObject *m_pCatGraphicsObject;
    CatGraphicPen* m_pCurrentCatGraphicPen;
};

#endif // CATGRAPHICSSCENE_H
