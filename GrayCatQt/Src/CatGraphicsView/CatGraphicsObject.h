#ifndef CATGRAPHICSOBJECT_H
#define CATGRAPHICSOBJECT_H

#include <QObject>

class CatGraphicsObject : public QObject
{
    Q_OBJECT
public:
    //
    enum CAT_DRAWINGBOARD_STATE {
        NO_STATE,
        SELECT,
        PEN,
        ERASER,
        TeachingPen
    };
    Q_ENUM(CAT_DRAWINGBOARD_STATE)

    explicit CatGraphicsObject(QObject *parent);
    ~CatGraphicsObject();

    CAT_DRAWINGBOARD_STATE GetDrawingBoardState() const { return m_yDrawingState; }
    CAT_DRAWINGBOARD_STATE GetLastDrawingBoardState() const { return m_yLastDrawingState; }

    void SetDrawingBoardState(CAT_DRAWINGBOARD_STATE state)
    {
        m_yLastDrawingState = m_yDrawingState;
        m_yDrawingState = state;
    }

private:

private:
    CAT_DRAWINGBOARD_STATE m_yDrawingState;
    CAT_DRAWINGBOARD_STATE m_yLastDrawingState;

};

#endif // CATGRAPHICSOBJECT_H
