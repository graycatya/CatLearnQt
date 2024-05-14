#ifndef QUICKSLIDERS_H
#define QUICKSLIDERS_H

#include <QWidget>

namespace Ui {
class QuickSliders;
}

class QuickSliders : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor rootBackgroundColor READ GetRootBackgroundColor WRITE SetRootBackgroundColor)
    Q_PROPERTY(QColor sliderBackgroundColor READ GetSliderBackgroundColor WRITE SetSliderBackgroundColor)
    Q_PROPERTY(QColor sliderColor READ GetSliderColor  WRITE SetSliderColor)
    Q_PROPERTY(QColor slidingBlockColor READ GetSlidingBlockColor WRITE SetSlidingBlockColor)
    Q_PROPERTY(QColor slidingBlockPressColor READ GetSlidingBlockPressColor WRITE SetSlidingBlockPressColor)
    Q_PROPERTY(QColor slidingBorderColor READ GetSlidingBorderColor WRITE SetSlidingBorderColor)
    Q_PROPERTY(QColor textColor READ GetTextColor WRITE SetTextColor)
public:
    explicit QuickSliders(QWidget *parent = nullptr);
    ~QuickSliders();

    QColor GetRootBackgroundColor() {
        return rootBackgroundColor;
    }

    QColor GetSliderBackgroundColor() {
        return sliderBackgroundColor;
    }

    QColor GetSliderColor() {
        return sliderColor;
    }

    QColor GetSlidingBlockColor() {
        return slidingBlockColor;
    }

    QColor GetSlidingBlockPressColor() {
        return slidingBlockPressColor;
    }

    QColor GetSlidingBorderColor() {
        return slidingBorderColor;
    }

    QColor GetTextColor() {
        return textColor;
    }

private:
    void InitUi();
    void InitProperty();
    void InitConnect();

    void UpdateStyle();

signals:
    void setRootBackgroundColor(QColor);
    void setSliderBackgroundColor(QColor);
    void setSliderColor(QColor);
    void setSlidingBlockColor(QColor);
    void setSlidingBlockPressColor(QColor);
    void setSlidingBorderColor(QColor);
    void setTextColor(QColor);

public slots:
    void SetRootBackgroundColor(QColor color);
    void SetSliderBackgroundColor(QColor color);
    void SetSliderColor(QColor color);
    void SetSlidingBlockColor(QColor color);
    void SetSlidingBlockPressColor(QColor color);
    void SetSlidingBorderColor(QColor color);
    void SetTextColor(QColor color);

private:
    Ui::QuickSliders *ui;
    QColor rootBackgroundColor;
    QColor sliderBackgroundColor;
    QColor sliderColor;
    QColor slidingBlockColor;
    QColor slidingBlockPressColor;
    QColor slidingBorderColor;
    QColor textColor;

};

#endif // QUICKSLIDERS_H
