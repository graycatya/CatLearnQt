﻿#ifndef CATGRAPHICSSCENE_H
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
    //QPointF lastpoint,endpoint; //存储鼠标的按下和放开时的坐标
    bool m_bpen;
};

#endif // CATGRAPHICSSCENE_H
