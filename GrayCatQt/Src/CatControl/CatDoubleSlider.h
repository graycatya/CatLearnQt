#ifndef CATDOUBLESLIDER_H
#define CATDOUBLESLIDER_H

#include <QWidget>

class CatDoubleSlider : public QWidget
{
    Q_OBJECT
    Q_ENUMS(OrientationState)
    Q_ENUMS(SliderStyle)
    Q_PROPERTY(int SlideLeftOrTopWidth READ SlideLeftOrTopWidth WRITE setSlideLeftOrTopWidth)
    Q_PROPERTY(int SlideLeftOrTopHeight READ SlideLeftOrTopHeight WRITE setSlideLeftOrTopHeight)
    Q_PROPERTY(int SlideRightOrBottomWidth READ SlideRightOrBottomWidth WRITE setSlideRightOrBottomWidth)
    Q_PROPERTY(int SlideRightOrBottomHeight READ SlideRightOrBottomHeight WRITE setSlideRightOrBottomHeight)
    Q_PROPERTY(OrientationState SlideOrientationState READ SlideOrientationState WRITE setSlideOrientationState)
    Q_PROPERTY(SliderStyle MySliderStyle READ MySliderStyle WRITE setMySliderStyle)

public:
    enum OrientationState {
        SliderHorizontal,
        SliderVertical
    };

    enum SliderStyle {
        SliderRect,
        SliderRound
    };

    explicit CatDoubleSlider(QWidget *parent = nullptr);
    ~CatDoubleSlider();

    int SlideLeftOrTopWidth() const { return m_ySlide_LeftOrTop.width(); }
    int SlideLeftOrTopHeight() const { return m_ySlide_LeftOrTop.height(); }
    int SlideRightOrBottomWidth() const { return m_ySlide_RightOrBottom.width(); }
    int SlideRightOrBottomHeight() const { return m_ySlide_RightOrBottom.height(); }
    OrientationState SlideOrientationState() const { return m_ySlideOrientationState; }
    SliderStyle MySliderStyle() const { return m_ySliderStyle; }

private:
    void InitUi();
    void InitProperty();

    void Painter_Background_Rect(QPainter *painter);
    void Painter_BackgroundSlide_Rect(QPainter *painter);
    void Painter_Slide_LeftOrTop(QPainter *painter);
    void Painter_Slide_RightOrBottom(QPainter *painter);

public slots:
    void setSlideLeftOrTopWidth(int width);
    void setSlideLeftOrTopHeight(int height);
    void setSlideRightOrBottomWidth(int width);
    void setSlideRightOrBottomHeight(int height);
    void setSlideOrientationState(OrientationState state);
    void setMySliderStyle(SliderStyle style);

protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;




private:
    QRect m_ySlide_LeftOrTop;
    QRect m_ySlide_RightOrBottom;
    QRect m_yBackground_Rect;
    QRect m_yBackgroundSlide_Rect;
    OrientationState m_ySlideOrientationState;
    SliderStyle m_ySliderStyle;

};

#endif // CATDOUBLESLIDER_H
