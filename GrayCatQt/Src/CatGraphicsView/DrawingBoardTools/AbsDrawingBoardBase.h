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
    void InitProperty();

private:
    QRectF m_ySize;     // Item 大小
    qint32 m_yPadding;  // 内边距 为透明部分

};

#endif // ABSDRAWINGBOARDBASE_H
