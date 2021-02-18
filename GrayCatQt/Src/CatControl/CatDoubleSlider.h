#ifndef CATDOUBLESLIDER_H
#define CATDOUBLESLIDER_H

#include <QWidget>

class CatDoubleSlider : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int SlideLeftOrTopWidth READ SlideLeftOrTopWidth WRITE setSlideLeftOrTopWidth NOTIFY SlideLeftOrTopWidthChanged)
    Q_PROPERTY(int SlideLeftOrTopHeight READ SlideLeftOrTopHeight WRITE setSlideLeftOrTopHeight NOTIFY SlideLeftOrTopHeightChanged)
    Q_PROPERTY(int SlideRightOrBottomWidth READ SlideRightOrBottomWidth WRITE setSlideRightOrBottomWidth NOTIFY SlideRightOrBottomWidthChanged)
    Q_PROPERTY(int SlideRightOrBottomHeight READ SlideRightOrBottomHeight WRITE setSlideRightOrBottomHeight NOTIFY SlideRightOrBottomHeightChanged)
    Q_PROPERTY(OrientationState SlideOrientationState READ SlideOrientationState WRITE setSlideOrientationState NOTIFY SlideOrientationStateChanged)
    Q_PROPERTY(SliderStyles SliderStyle READ SliderStyle WRITE setSliderStyle NOTIFY SliderStyleChanged)

    Q_PROPERTY(QBrush SlideLeftColor READ SlideLeftColor WRITE setSlideLeftColor NOTIFY SlideLeftColorChanged)
    Q_PROPERTY(QBrush SlideRightColor READ SlideRightColor WRITE setSlideRightColor NOTIFY SlideRightColorChanged)
    Q_PROPERTY(QBrush BackgroundRectColor READ BackgroundRectColor WRITE setBackgroundRectColor NOTIFY BackgroundRectColorChanged)
    Q_PROPERTY(QBrush BackgroundSlideRectColor READ BackgroundSlideRectColor WRITE setBackgroundSlideRectColor NOTIFY BackgroundSlideRectColorChanged)
    Q_PROPERTY(QBrush SlideLeftBorderColor READ SlideLeftBorderColor WRITE setSlideLeftBorderColor NOTIFY SlideLeftBorderColorChanged)
    Q_PROPERTY(QBrush SlideRightBorderColor READ SlideRightBorderColor WRITE setSlideRightBorderColor NOTIFY SlideRightBorderColorChanged)
    Q_PROPERTY(QBrush BackgroundRectBorderColor READ BackgroundRectBorderColor WRITE setBackgroundRectBorderColor NOTIFY BackgroundRectBorderColorChanged)
    Q_PROPERTY(QBrush BackgroundSlideRectBorderColor READ BackgroundSlideRectBorderColor WRITE setBackgroundSlideRectBorderColor NOTIFY BackgroundSlideRectBorderColorChanged)

    Q_PROPERTY(QBrush HoverSlideLeftColor READ HoverSlideLeftColor WRITE setHoverSlideLeftColor NOTIFY HoverSlideLeftColorChanged)
    Q_PROPERTY(QBrush HoverSlideRightColor READ HoverSlideRightColor WRITE setHoverSlideRightColor NOTIFY HoverSlideRightColorChanged)
    Q_PROPERTY(QBrush HoverBackgroundRectColor READ HoverBackgroundRectColor WRITE setHoverBackgroundRectColor NOTIFY HoverBackgroundRectColorChanged)
    Q_PROPERTY(QBrush HoverBackgroundSlideRectColor READ HoverBackgroundSlideRectColor WRITE setHoverBackgroundSlideRectColor NOTIFY HoverBackgroundSlideRectColorChanged)
    Q_PROPERTY(QBrush HoverSlideLeftBorderColor READ HoverSlideLeftBorderColor WRITE setHoverSlideLeftBorderColor NOTIFY HoverSlideLeftBorderColorChanged)
    Q_PROPERTY(QBrush HoverSlideRightBorderColor READ HoverSlideRightBorderColor WRITE setHoverSlideRightBorderColor NOTIFY HoverSlideRightBorderColorChanged)
    Q_PROPERTY(QBrush HoverBackgroundRectBorderColor READ HoverBackgroundRectBorderColor WRITE setHoverBackgroundRectBorderColor NOTIFY HoverBackgroundRectBorderColorChanged)
    Q_PROPERTY(QBrush HoverBackgroundSlideRectBorderColor READ HoverBackgroundSlideRectBorderColor WRITE setHoverBackgroundSlideRectBorderColor NOTIFY HoverBackgroundSlideRectBorderColorChanged)

    Q_PROPERTY(QBrush PressSlideLeftColor READ PressSlideLeftColor WRITE setPressSlideLeftColor NOTIFY PressSlideLeftColorChanged)
    Q_PROPERTY(QBrush PressSlideRightColor READ PressSlideRightColor WRITE setPressSlideRightColor NOTIFY PressSlideRightColorChanged)
    Q_PROPERTY(QBrush PressBackgroundRectColor READ PressBackgroundRectColor WRITE setPressBackgroundRectColor NOTIFY PressBackgroundRectColorChanged)
    Q_PROPERTY(QBrush PressBackgroundSlideRectColor READ PressBackgroundSlideRectColor WRITE setPressBackgroundSlideRectColor NOTIFY PressBackgroundSlideRectColorChanged)
    Q_PROPERTY(QBrush PressSlideLeftBorderColor READ PressSlideLeftBorderColor WRITE setPressSlideLeftBorderColor NOTIFY PressSlideLeftBorderColorChanged)
    Q_PROPERTY(QBrush PressSlideRightBorderColor READ PressSlideRightBorderColor WRITE setPressSlideRightBorderColor NOTIFY PressSlideRightBorderColorChanged)
    Q_PROPERTY(QBrush PressBackgroundRectBorderColor READ PressBackgroundRectBorderColor WRITE setPressBackgroundRectBorderColor NOTIFY PressBackgroundRectBorderColorChanged)
    Q_PROPERTY(QBrush PressBackgroundSlideRectBorderColor READ PressBackgroundSlideRectBorderColor WRITE setPressBackgroundSlideRectBorderColor NOTIFY PressBackgroundSlideRectBorderColorChanged)

    Q_PROPERTY(int BackgroundRadius READ BackgroundRadius WRITE setBackgroundRadius NOTIFY BackgroundRadiusChanged)
    Q_PROPERTY(int SlideRadius READ SlideRadius WRITE setSlideRadius NOTIFY SlideRadiusChanged)

    Q_PROPERTY(qreal SlideWidth READ SlideWidth WRITE setSlideWidth NOTIFY SlideWidthChanged)
    Q_PROPERTY(qreal BackgroundHeight READ BackgroundHeight WRITE setBackgroundHeight NOTIFY BackgroundHeightChanged)
    Q_PROPERTY(qreal BackgroundSlideHeight READ BackgroundSlideHeight WRITE setBackgroundSlideHeight NOTIFY BackgroundSlideHeightChanged)
    Q_PROPERTY(qreal SlideLeftBorderWidth READ SlideLeftBorderWidth WRITE setSlideLeftBorderWidth NOTIFY SlideLeftBorderWidthChanged)
    Q_PROPERTY(qreal SlideRightBorderWidth READ SlideRightBorderWidth WRITE setSlideRightBorderWidth NOTIFY SlideRightBorderWidthChanged)
    Q_PROPERTY(qreal BackgroundRectBorderWidth READ BackgroundRectBorderWidth WRITE setBackgroundRectBorderWidth NOTIFY BackgroundRectBorderWidthChanged)
    Q_PROPERTY(qreal BackgroundSlideRectBorderWidth READ BackgroundSlideRectBorderWidth WRITE setBackgroundSlideRectBorderWidth NOTIFY BackgroundSlideRectBorderWidthChanged)


public:
    enum OrientationState {
        SliderHorizontal,
        SliderVertical
    };

    Q_ENUM(OrientationState)
    enum SliderStyles {
        SliderRect,
        SliderRound
    };

    Q_ENUM(SliderStyles)
    enum SelectStyle {
        LeftOrTopSelect,
        RightOrBottomSelect,
        BackgroundSlideSelect,
        NotSelect
    };

    explicit CatDoubleSlider(QWidget *parent = nullptr);
    ~CatDoubleSlider();

    int SlideLeftOrTopWidth() const { return m_ySlide_LeftOrTop.width(); }
    int SlideLeftOrTopHeight() const { return m_ySlide_LeftOrTop.height(); }
    int SlideRightOrBottomWidth() const { return m_ySlide_RightOrBottom.width(); }
    int SlideRightOrBottomHeight() const { return m_ySlide_RightOrBottom.height(); }
    OrientationState SlideOrientationState() const { return m_ySlideOrientationState; }
    SliderStyles SliderStyle() const { return m_ySliderStyle; }

    QBrush SlideLeftColor() const { return m_cSlideLeftColor; }
    QBrush SlideRightColor() const { return m_cSlideRightColor; }
    QBrush BackgroundRectColor() const { return m_cBackgroundRectColor; }
    QBrush BackgroundSlideRectColor() const { return m_cBackgroundSlideRectColor; }
    QBrush SlideLeftBorderColor() const { return m_cSlideLeftBorderColor; }
    QBrush SlideRightBorderColor() const { return m_cSlideRightBorderColor; }
    QBrush BackgroundRectBorderColor() const { return m_cBackgroundRectBorderColor; }
    QBrush BackgroundSlideRectBorderColor() const { return m_cBackgroundSlideRectBorderColor; }

    QBrush HoverSlideLeftColor() const { return m_cHoverSlideLeftColor; }
    QBrush HoverSlideRightColor() const { return m_cHoverSlideRightColor; }
    QBrush HoverBackgroundRectColor() const { return m_cHoverBackgroundRectColor; }
    QBrush HoverBackgroundSlideRectColor() const { return m_cHoverBackgroundSlideRectColor; }
    QBrush HoverSlideLeftBorderColor() const { return m_cHoverSlideLeftBorderColor; }
    QBrush HoverSlideRightBorderColor() const { return m_cHoverSlideRightBorderColor; }
    QBrush HoverBackgroundRectBorderColor() const { return m_cHoverBackgroundRectBorderColor; }
    QBrush HoverBackgroundSlideRectBorderColor() const { return m_cHoverBackgroundSlideRectBorderColor; }

    QBrush PressSlideLeftColor() const { return m_cPressSlideLeftColor; }
    QBrush PressSlideRightColor() const { return m_cPressSlideRightColor; }
    QBrush PressBackgroundRectColor() const { return m_cPressBackgroundRectColor; }
    QBrush PressBackgroundSlideRectColor() const { return m_cPressBackgroundSlideRectColor; }
    QBrush PressSlideLeftBorderColor() const { return m_cPressSlideLeftBorderColor; }
    QBrush PressSlideRightBorderColor() const { return m_cPressSlideRightBorderColor; }
    QBrush PressBackgroundRectBorderColor() const { return m_cPressBackgroundRectBorderColor; }
    QBrush PressBackgroundSlideRectBorderColor() const { return m_cPressBackgroundSlideRectBorderColor; }

    int BackgroundRadius() const { return m_nBackgroundRadius; }
    int SlideRadius() const { return m_nSlideRadius; }

    qreal SlideWidth() const { return m_nSlideWidth; }
    qreal BackgroundHeight() const { return m_nBackgroundHeight; }
    qreal BackgroundSlideHeight() const { return m_nBackgroundSlideHeight; }
    qreal SlideLeftBorderWidth() const { return m_nSlideLeftBorderWidth; }
    qreal SlideRightBorderWidth() const { return m_nSlideRightBorderWidth; }
    qreal BackgroundRectBorderWidth() const { return m_nBackgroundRectBorderWidth; }
    qreal BackgroundSlideRectBorderWidth() const { return m_nBackgroundSlideRectBorderWidth; }

    void SetFromTo(qreal from, qreal to);
    void SetFirst(qreal first);
    void SetSecond(qreal second);

private:
    void InitUi();
    void InitProperty();

    void InitRectfProperty();

    void UpdateBackgroundSlide();

    void Painter_Background_Rect(QPainter *painter);
    void Painter_BackgroundSlide_Rect(QPainter *painter);
    void Painter_Slide_LeftOrTop(QPainter *painter);
    void Painter_Slide_RightOrBottom(QPainter *painter);

    void LeftOrTopSelectDisPose(QMouseEvent *event);
    void RightOrBottomSelectDisPose(QMouseEvent *event);
    void BackgroundSlideRectPose(QMouseEvent *event);

    void UpdateOrientation();
    void UpdateFirstSecond();

    void UpdateSlideCoordinates();

signals:
    void SlideLeftOrTopWidthChanged(int);
    void SlideLeftOrTopHeightChanged(int);
    void SlideRightOrBottomWidthChanged(int);
    void SlideRightOrBottomHeightChanged(int);
    void SlideOrientationStateChanged(CatDoubleSlider::OrientationState);
    void SliderStyleChanged(CatDoubleSlider::SliderStyles);

    void SlideLeftColorChanged(QBrush);
    void SlideRightColorChanged(QBrush);
    void BackgroundRectColorChanged(QBrush);
    void BackgroundSlideRectColorChanged(QBrush);
    void SlideLeftBorderColorChanged(QBrush);
    void SlideRightBorderColorChanged(QBrush);
    void BackgroundRectBorderColorChanged(QBrush);
    void BackgroundSlideRectBorderColorChanged(QBrush);

    void HoverSlideLeftColorChanged(QBrush);
    void HoverSlideRightColorChanged(QBrush);
    void HoverBackgroundRectColorChanged(QBrush);
    void HoverBackgroundSlideRectColorChanged(QBrush);
    void HoverSlideLeftBorderColorChanged(QBrush);
    void HoverSlideRightBorderColorChanged(QBrush);
    void HoverBackgroundRectBorderColorChanged(QBrush);
    void HoverBackgroundSlideRectBorderColorChanged(QBrush);

    void PressSlideLeftColorChanged(QBrush);
    void PressSlideRightColorChanged(QBrush);
    void PressBackgroundRectColorChanged(QBrush);
    void PressBackgroundSlideRectColorChanged(QBrush);
    void PressSlideLeftBorderColorChanged(QBrush);
    void PressSlideRightBorderColorChanged(QBrush);
    void PressBackgroundRectBorderColorChanged(QBrush);
    void PressBackgroundSlideRectBorderColorChanged(QBrush);

    void BackgroundRadiusChanged(int);
    void SlideRadiusChanged(int);
    void SlideWidthChanged(qreal);
    void BackgroundHeightChanged(qreal);
    void BackgroundSlideHeightChanged(qreal);
    void SlideLeftBorderWidthChanged(qreal);
    void SlideRightBorderWidthChanged(qreal);
    void BackgroundRectBorderWidthChanged(qreal);
    void BackgroundSlideRectBorderWidthChanged(qreal);

    void UpdateFirstSeconded(qreal, qreal);

public slots:
    void setSlideLeftOrTopWidth(int width);
    void setSlideLeftOrTopHeight(int height);
    void setSlideRightOrBottomWidth(int width);
    void setSlideRightOrBottomHeight(int height);
    void setSlideOrientationState(CatDoubleSlider::OrientationState state);
    void setSliderStyle(CatDoubleSlider::SliderStyles style);

    void setSlideLeftColor(QBrush brush);
    void setSlideRightColor(QBrush brush);
    void setBackgroundRectColor(QBrush brush);
    void setBackgroundSlideRectColor(QBrush brush);
    void setSlideLeftBorderColor(QBrush color);
    void setSlideRightBorderColor(QBrush color);
    void setBackgroundRectBorderColor(QBrush color);
    void setBackgroundSlideRectBorderColor(QBrush color);

    void setHoverSlideLeftColor(QBrush brush);
    void setHoverSlideRightColor(QBrush brush);
    void setHoverBackgroundRectColor(QBrush brush);
    void setHoverBackgroundSlideRectColor(QBrush brush);
    void setHoverSlideLeftBorderColor(QBrush color);
    void setHoverSlideRightBorderColor(QBrush color);
    void setHoverBackgroundRectBorderColor(QBrush color);
    void setHoverBackgroundSlideRectBorderColor(QBrush color);

    void setPressSlideLeftColor(QBrush brush);
    void setPressSlideRightColor(QBrush brush);
    void setPressBackgroundRectColor(QBrush brush);
    void setPressBackgroundSlideRectColor(QBrush brush);
    void setPressSlideLeftBorderColor(QBrush color);
    void setPressSlideRightBorderColor(QBrush color);
    void setPressBackgroundRectBorderColor(QBrush color);
    void setPressBackgroundSlideRectBorderColor(QBrush color);

    void setBackgroundRadius(int radius);
    void setSlideRadius(int radius);

    void setSlideWidth(qreal width);
    void setBackgroundHeight(qreal height);
    void setBackgroundSlideHeight(qreal height);
    void setSlideLeftBorderWidth(qreal width);
    void setSlideRightBorderWidth(qreal width);
    void setBackgroundRectBorderWidth(qreal width);
    void setBackgroundSlideRectBorderWidth(qreal width);

protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    bool eventFilter(QObject *o, QEvent *e) override;

private:
    QRectF m_ySlide_LeftOrTop;
    QRectF m_ySlide_RightOrBottom;
    QRectF m_yBackground_Rect;
    QRectF m_yBackgroundSlide_Rect;
    OrientationState m_ySlideOrientationState;
    SliderStyles m_ySliderStyle;

    QBrush m_cCurrentSlideLeftColor;
    QBrush m_cCurrentSlideRightColor;
    QBrush m_cCurrentBackgroundRectColor;
    QBrush m_cCurrentBackgroundSlideRectColor;
    QBrush m_cCurrentSlideLeftBorderColor;
    QBrush m_cCurrentSlideRightBorderColor;
    QBrush m_cCurrentBackgroundRectBorderColor;
    QBrush m_cCurrentBackgroundSlideRectBorderColor;

    QBrush m_cSlideLeftColor;
    QBrush m_cSlideRightColor;
    QBrush m_cBackgroundRectColor;
    QBrush m_cBackgroundSlideRectColor;
    QBrush m_cSlideLeftBorderColor;
    QBrush m_cSlideRightBorderColor;
    QBrush m_cBackgroundRectBorderColor;
    QBrush m_cBackgroundSlideRectBorderColor;

    QBrush m_cHoverSlideLeftColor;
    QBrush m_cHoverSlideRightColor;
    QBrush m_cHoverBackgroundRectColor;
    QBrush m_cHoverBackgroundSlideRectColor;
    QBrush m_cHoverSlideLeftBorderColor;
    QBrush m_cHoverSlideRightBorderColor;
    QBrush m_cHoverBackgroundRectBorderColor;
    QBrush m_cHoverBackgroundSlideRectBorderColor;

    QBrush m_cPressSlideLeftColor;
    QBrush m_cPressSlideRightColor;
    QBrush m_cPressBackgroundRectColor;
    QBrush m_cPressBackgroundSlideRectColor;
    QBrush m_cPressSlideLeftBorderColor;
    QBrush m_cPressSlideRightBorderColor;
    QBrush m_cPressBackgroundRectBorderColor;
    QBrush m_cPressBackgroundSlideRectBorderColor;

    int m_nBackgroundRadius;
    int m_nSlideRadius;

    qreal m_nSlideWidth;
    qreal m_nBackgroundHeight;
    qreal m_nBackgroundSlideHeight;
    qreal m_nSlideLeftBorderWidth;
    qreal m_nSlideRightBorderWidth;
    qreal m_nBackgroundRectBorderWidth;
    qreal m_nBackgroundSlideRectBorderWidth;

    qreal m_nSliderDistance;

    SelectStyle m_ySelectStyle;
    SelectStyle m_yLastSelectStyle;
    QPointF m_pPressPoint;

    qreal m_nFrom;
    qreal m_nTo;
    qreal m_nFirst;
    qreal m_nSecond;

    bool m_bMousePress;

};

#endif // CATDOUBLESLIDER_H
