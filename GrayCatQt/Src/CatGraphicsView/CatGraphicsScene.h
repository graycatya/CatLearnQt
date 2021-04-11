#ifndef CATGRAPHICSSCENE_H
#define CATGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QTouchEvent>

#include "CatGraphicsObject.h"

class CatGraphicsView;
class TeachingToolCompass;
class TeachingToolProtractor;
class TeachingToolRuler;
class TeachingToolTrangle;

class CatBrushPixItem;

class CatGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit CatGraphicsScene(QObject *parent = nullptr);
    ~CatGraphicsScene();

    void InitProperty();

    void SetView(CatGraphicsView *view);
    CatGraphicsView *View( void );


    void AddTeachingToolProtractor();
    void AddTeachingToolRuler();
    void AddTeachingToolTrangle();
    void AddTeachingToolCompass();

    void Clear();

private:

    void mousePressEventPenState(QGraphicsSceneMouseEvent *event);
    void mouseMoveEventPenState(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEventPenState(QGraphicsSceneMouseEvent *event);

protected:
    bool event(QEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    bool touchEvent(QTouchEvent *event);
    bool scenePress(int id, const QPointF &pos);
    bool sceneMove(int id, const QPointF &presspos, const QPointF &pos);
    bool sceneRelease(int id, const QPointF &pos);

public slots:
    void On_DrawingBoard_SelectState();
    void On_DrawingBoard_PenState();
    void On_DrawingBoard_EraserState();

private:
    CatGraphicsView *m_yView;
    QVector<TeachingToolCompass*> m_pTeachingToolCompass;
    QVector<TeachingToolProtractor*> m_pTeachingToolProtractor;
    QVector<TeachingToolRuler*> m_pTeachingToolRuler;
    QVector<TeachingToolTrangle*> m_pTeachingToolTrangle;
    CatBrushPixItem *m_pCatBrushPixItem;


    CatGraphicsObject *m_pCatGraphicsObject;

    bool m_bMousePress;
};

#endif // CATGRAPHICSSCENE_H
