#ifndef CATDOUBLESLIDER_H
#define CATDOUBLESLIDER_H

#include <QWidget>

class CatDoubleSlider : public QWidget
{
    Q_OBJECT
    //Q_ENUMS(OrientationState)
    //Q_ENUMS(SliderStyle)
    Q_PROPERTY(int SlideLeftOrTopWidth READ SlideLeftOrTopWidth WRITE setSlideLeftOrTopWidth NOTIFY SlideLeftOrTopWidthChanged)
    Q_PROPERTY(int SlideLeftOrTopHeight READ SlideLeftOrTopHeight WRITE setSlideLeftOrTopHeight NOTIFY SlideLeftOrTopHeightChanged)
    Q_PROPERTY(int SlideRightOrBottomWidth READ SlideRightOrBottomWidth WRITE setSlideRightOrBottomWidth NOTIFY SlideRightOrBottomWidthChanged)
    Q_PROPERTY(int SlideRightOrBottomHeight READ SlideRightOrBottomHeight WRITE setSlideRightOrBottomHeight NOTIFY SlideRightOrBottomHeightChanged)
    Q_PROPERTY(OrientationState SlideOrientationState READ SlideOrientationState WRITE setSlideOrientationState NOTIFY SlideOrientationStateChanged)
    Q_PROPERTY(SliderStyle MySliderStyle READ MySliderStyle WRITE setMySliderStyle NOTIFY MySliderStyleChanged)

public:
    enum OrientationState {
        SliderHorizontal,
        SliderVertical
    };
    Q_ENUM(OrientationState)
    enum SliderStyle {
        SliderRect,
        SliderRound
    };
    Q_ENUM(SliderStyle)

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

signals:
    void SlideLeftOrTopWidthChanged(int);
    void SlideLeftOrTopHeightChanged(int);
    void SlideRightOrBottomWidthChanged(int);
    void SlideRightOrBottomHeightChanged(int);
    void SlideOrientationStateChanged(CatDoubleSlider::OrientationState);
    void MySliderStyleChanged(CatDoubleSlider::SliderStyle);

public slots:
    void setSlideLeftOrTopWidth(int width);
    void setSlideLeftOrTopHeight(int height);
    void setSlideRightOrBottomWidth(int width);
    void setSlideRightOrBottomHeight(int height);
    void setSlideOrientationState(CatDoubleSlider::OrientationState state);
    void setMySliderStyle(CatDoubleSlider::SliderStyle style);

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
