#ifndef PROCESSOBJECT_H
#define PROCESSOBJECT_H

#include <QObject>
#include <QPoint>
#include <QSize>

class ProcessObject : public QObject
{
    Q_OBJECT
public:
    explicit ProcessObject(QObject *parent = nullptr);
    ~ProcessObject();

public:
    // SELECT(选择状态-设置初始大小)， MOVE(移动状态), ZOOM(修改大小状态)
    enum STATE {SELECT, MOVE, ZOOM, TOP_ZOOM, BOTTOM_ZOOM, LEFT_ZOOM, RIGHT_ZOOM};

    void SetGeometry(int x, int y, int width, int height);

    void SetMinWidth(int width);
    int GetMinWidth( void ) const;

    void SetMinHeight(int height);
    int GetMinHeight( void ) const;

    void SetMinSize(QSize size);
    QSize GetMinSize( void ) const;

    void SetMaxWidth(int width);
    int GetMaxWidth( void ) const;

    void SetMaxHeight(int height);
    int GetMaxHeight( void ) const;

    void SetMaxSize(QSize size);
    QSize GetMaxSize( void ) const;

    // 父对象最大活动范围
    void SetMaxParentSize( QSize maxparentsize );
    QSize GetMaxParentSize( void ) const;
    int GetMaxParentWidget( void ) const;
    int GetMaxParentHeight( void ) const;

    int x( void ) const;
    int y( void ) const;
    int width( void ) const;
    int height( void ) const;

    // 判断是否在选取区域内
    bool IsInArea(QPoint pos);

    // 移动区域
    void Move(QPoint pos);

    // 设置状态
    void SetState( STATE state );
    // 获取状态
    STATE GetState( void ) const;

    void SetStart(QPoint pos);
    QPoint GetStart( void ) const;

    void SetEnd(QPoint pos);
    QPoint GetEnd( void ) const;

    QPoint GetLeftTopPos( void ) const;

    QPoint GetRightBottomPos( void ) const;

private:
    // 比较两点位置
    void ComparePoint(QPoint &leftTop, QPoint &rightBottom);

private:
    QPoint m_qLeftTopPos, m_qRightBottomPos, m_qRightTopPos, m_qLeftBottomPos;
    QPoint m_qStartPos, m_qEndPos;
    int MinWidth, MinHeight;
    int MaxWidth, MaxHeight;

    // 在父对象活动范围大小
    int MaxParentWidth, MaxParentHeight;

    STATE m_qstate;

};

#endif // PROCESSOBJECT_H
