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
        ERASER
    };
    Q_ENUM(CAT_DRAWINGBOARD_STATE)

    explicit CatGraphicsObject(QObject *parent);
    ~CatGraphicsObject();

    CAT_DRAWINGBOARD_STATE GetDrawingBoardState() const { return m_yDrawingState; }
    void SetDrawingBoardState(CAT_DRAWINGBOARD_STATE state) { m_yDrawingState = state; }

private:

private:
    CAT_DRAWINGBOARD_STATE m_yDrawingState;

};

#endif // CATGRAPHICSOBJECT_H
