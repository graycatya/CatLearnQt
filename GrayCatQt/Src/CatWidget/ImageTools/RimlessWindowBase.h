#ifndef RIMLESSWINDOWBASE_H
#define RIMLESSWINDOWBASE_H

#include <QWidget>

class ProcessObject;

class RimlessWindowBase : public QWidget
{
    Q_OBJECT
public:
    explicit RimlessWindowBase(QWidget *parent = nullptr);
    ~RimlessWindowBase();

private:
    void InitProperty();
    bool ZoomIsInArea(QRect rect, QPoint pos);

private:

    QRect m_qTopLeft;
    QRect m_qTopRight;

    QRect m_qBottomLeft;
    QRect m_qBottomRight;



    ProcessObject *m_pScreen;  // 处理屏幕的对象

};

#endif // RIMLESSWINDOWBASE_H
