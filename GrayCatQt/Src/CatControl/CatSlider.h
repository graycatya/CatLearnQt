#ifndef CATSLIDER_H
#define CATSLIDER_H

#include <QWidget>


class CatSlider : public QWidget
{
    Q_OBJECT
public:
    //控件样式
    enum SliderStyle
    {
        Single_HorizontalSlider,	//水平样式单滑块
        Single_VerticalSlider,		//垂直样式单化快
        Double_HorizontalSlider,	//水平样式双滑块
        Double_VerticalSlider,		//垂直样式双滑块
    };

    //滑块样式
    enum HandleStyle
    {
        Polygon,	//多边形滑块
        Rectangle,	//矩形滑块
        Ellipse,	//圆形滑块
    };
    explicit CatSlider(QWidget *parent = nullptr);
    ~CatSlider();

signals:
    void valueChanged(float min, float max);

protected:
    void resizeEvent(QResizeEvent *event);		//改变窗口大小事件
    void paintEvent(QPaintEvent *event);		//绘制事件
    void mousePressEvent(QMouseEvent *event);	//鼠标按下事件
    void mouseMoveEvent(QMouseEvent *event);	//鼠标移动事件
    void mouseReleaseEvent(QMouseEvent *event);	//鼠标弹起事件
    void keyPressEvent(QKeyEvent *event);		//键盘按下事件
    void keyReleaseEvent(QKeyEvent *event);		//键盘弹起事件
    void enterEvent(QEvent *event);				//鼠标进入窗口事件
    void leaveEvent(QEvent* event);				//鼠标离开窗口事件

protected:
    void paintPolygon(QPolygon polygon, QColor color, QPainter* painter);	//绘制多边形
    void paintRectangle(QRect rect, QColor color, QPainter* painter);		//绘制矩形
    void paintEllipse(QRect rect, QColor color, QPainter* painter);			//绘制圆形
    void paintSlider(QPainter* painter);									//绘制槽
    void paintText(QPainter* painter);										//绘制文本
    void paintHandle(QPainter* painter);									//绘制滑块
    void calculationPos(QPoint pot);										//计算坐标点

private:
    enum MouseState {
        MinHandle,
        MaxHandle,
        MoveRectHandle,
        None
    };

    void InitUi();
    void InitProperty();

private:
    float m_MinRange;		//最小范围
    float m_MaxRange;		//最大范围
    float m_curMinValue;	//当前最小值
    float m_curMaxValue;	//当前最大值
    float m_singleStep;		//按键单步步长

    QPolygon minHandlePolygon;	//左滑块(多边形)
    QPolygon maxHandlePolygon;	//右滑块(多边形)
    QRect minHandleRect;		//左滑块(矩形)
    QRect maxHandleRect;		//右滑块(矩形)
    QRect SelectionRect;        //中间滑块(矩形)

    SliderStyle m_SliderStyle;	//滑条样式：水平条、垂直条
    HandleStyle m_HandleStyle;	//滑块样式：多边形、矩形、圆形
    MouseState m_state;				//鼠标操作的滑块
    MouseState m_lastHandle;		//上次点击的滑块

    QColor m_sliderColor;			//槽底色
    QColor m_sliderSelectionColor;	//槽选中色
    QColor m_sliderHandleColor;		//滑块选中色
    QColor m_unSliderHandleColor;	//滑块未选中色

    QPoint m_pMousePress;           //鼠标坐标

    int m_minX, m_minY, m_maxX, m_maxY;	//左，右滑块的x，y坐标

    bool m_isDrawText;		//是否绘制文本
    bool m_textBrush;		//绘制文本背景
    bool m_isOverlap;		//是否允许滑块重叠
    int m_overlapOffset;	//重叠偏移量

public:
    // 接口
    float getMinRange() const;				//获取最小范围
    float getMaxRange() const;				//获取最大范围
    float getCurMinValue() const;			//获取当前最小值
    float getCurMaxValue() const;			//获取当前最大值

    void setOverlap(bool bl);											//设置是否允许滑块重叠
    void setStyle(SliderStyle sliderStyle, HandleStyle handleStyle);	//设置控件样式、滑块样式
    void setSliderColor(QColor botColor, QColor selColor);				//设置槽底色、选中色
    void setHandleColor(QColor selColor, QColor unSelColor);			//设置滑块选中色、未选中色
    void setRange(float min, float max);	//设置有效值范围
    void setMinRange(float value);			//设置最小范围
    void setMaxRange(float value);			//设置最大范围
    void setCurMinValue(float value);		//设置当前最小值
    void setCurMaxRange(float value);		//设置当前最大值
    void setSingleStep(float step);			//设置按键移动步长
};

#endif // CATSLIDER_H
