#ifndef QUICKSLIDERS_H
#define QUICKSLIDERS_H

#include <QWidget>

namespace Ui {
class QuickSliders;
}

class QuickSliders : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor rootBackgroundColor WRITE SetRootBackgroundColor)
    Q_PROPERTY(QColor sliderBackgroundColor WRITE SetSliderBackgroundColor)
    Q_PROPERTY(QColor sliderColor WRITE SetSliderColor)
    Q_PROPERTY(QColor slidingBlockColor WRITE SetSlidingBlockColor)
    Q_PROPERTY(QColor slidingBlockPressColor WRITE SetSlidingBlockPressColor)
    Q_PROPERTY(QColor slidingBorderColor WRITE SetSlidingBorderColor)
    Q_PROPERTY(QColor textColor WRITE SetTextColor)
public:
    explicit QuickSliders(QWidget *parent = nullptr);
    ~QuickSliders();

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
};

#endif // QUICKSLIDERS_H
