#ifndef ABSDRAWINGBOARDBASE_H
#define ABSDRAWINGBOARDBASE_H

#include <QObject>
#include <QRectF>

class AbsDrawingBoardBase : public QObject
{
    Q_OBJECT
public:
    explicit AbsDrawingBoardBase(QObject *parent = nullptr);
    ~AbsDrawingBoardBase();

protected:
    void SetBaseItemSize(QRectF size) { m_ySize = size; }
    QRectF GetBaseItemSize() const { return m_ySize; }

private:
    QRectF m_ySize;

};

#endif // ABSDRAWINGBOARDBASE_H
