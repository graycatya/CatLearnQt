
#pragma once

#include <qslider.h>
#include <qstyle.h>
#include <QMouseEvent>
#include <qpainter.h>
#include <qstyleoption.h>
#include <qpalette.h>
#include <qapplication.h>
#include <QDebug>

class RangeSlider : public QSlider {
    Q_OBJECT
public:
    RangeSlider(Qt::Orientation ot, QWidget *parent=nullptr)
        : QSlider(ot) {
        this->lowLimit = this->minimum();
        this->highLimit = this->maximum();
        this->pressed_control = QStyle::SC_None;
        this->tick_interval = 0;
        this->tick_position = QSlider::NoTicks;
        this->hover_control = QStyle::SC_None;
        this->click_offset = 0;
        this->active_slider = 0;
    }
    int low() { return this->lowLimit; }                            //获取滑块低位值
    void setLow(int low_limit)  {this->lowLimit = low_limit;}       //设置滑块低位值
    int high() { return this->highLimit;}                           //获取滑块高位值
    void setHigh(int high_limit) {this->highLimit = high_limit;}    //设置滑块高位值
    void setLimit(int high,int low, int step)                       //设置滑块的地高位以及差值
    {
        this->lowLimit = low;
        this->highLimit = high>(low+1)?high:(low+1);
        this->setPageStep(step);
        update();
        emit this->sliderMoved(this->lowLimit, this->highLimit);
    }
signals:
    void sliderMoved(int, int);

private:

protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        QStyleOptionSlider opt;

        // Draw groove
        this->initStyleOption(&opt);
        opt.sliderValue = 0;
        opt.sliderPosition = 0;
        opt.subControls = QStyle::SC_SliderGroove;
        if (this->tickPosition() != NoTicks) opt.subControls |= QStyle::SC_SliderTickmarks;
        this->style()->drawComplexControl(QStyle::CC_Slider, &opt, &painter, this);
        QRect groove = this->style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderGroove, this);

        // Draw span
        this->initStyleOption(&opt);
        opt.subControls = QStyle::SC_SliderGroove;
        opt.sliderValue = 0;
        opt.sliderPosition = this->lowLimit;
        QRect low_rect = this->style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);
        opt.sliderPosition = this->highLimit;
        QRect high_rect = this->style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);

        int low_pos = this->pick(low_rect.center());
        int high_pos = this->pick(high_rect.center());
        int min_pos = std::min(low_pos, high_pos);
        int max_pos = std::max(low_pos, high_pos);

        QPoint c = QRect(low_rect.center(), high_rect.center()).center();
        QRect span_rect;
        if (opt.orientation == Qt::Horizontal) {
            span_rect = QRect(QPoint(min_pos, c.y()-2), QPoint(max_pos, c.y()+1));
            groove.adjust(0,0,-1,0);
        } else {
            span_rect = QRect(QPoint(c.x()-2, min_pos), QPoint(c.x()+1, max_pos));
            groove.adjust(0,0,0,-1);
        }

        if (1) {
            QColor highlight = this->palette().color(QPalette::Highlight);
            painter.setBrush(QBrush(highlight));
            painter.setPen(QPen(highlight,0));
            painter.drawRect(span_rect.intersected(groove));
        }

        QStyle* style = QApplication::style();
        this->initStyleOption(&opt);
        opt.subControls = QStyle::SC_SliderHandle; // | QStyle::SC_SliderGroove;
        if (this->tickPosition() != QSlider::NoTicks) opt.subControls |= QStyle::SC_SliderTickmarks;
        if (this->pressed_control) opt.activeSubControls = this->pressed_control;
        else opt.activeSubControls = this->hover_control;
        opt.sliderPosition = this->lowLimit;
        opt.sliderValue = this->lowLimit;
        style->drawComplexControl(QStyle::CC_Slider, &opt, &painter, this);

        this->initStyleOption(&opt);
        opt.subControls = QStyle::SC_SliderHandle;
        if (this->tickPosition() != QSlider::NoTicks) opt.subControls |= QStyle::SC_SliderTickmarks;
        if (this->pressed_control) opt.activeSubControls = this->pressed_control;
        else opt.activeSubControls = this->hover_control;
        opt.sliderPosition = this->highLimit;
        opt.sliderValue = this->highLimit;
        style->drawComplexControl(QStyle::CC_Slider, &opt, &painter, this);
    }

    void mousePressEvent(QMouseEvent *ev) override {
        if (ev->button() == Qt::LeftButton) {
            ev->accept();
            QStyleOptionSlider opt;
            this->initStyleOption(&opt);
            this->active_slider = -1;

            QStyle* style = QApplication::style();
            QStyle::SubControl hit;

            opt.sliderPosition = this->lowLimit;
            hit = style->hitTestComplexControl(QStyle::CC_Slider, &opt, ev->pos(), this);
            if (hit == QStyle::SC_SliderHandle) {
                this->active_slider = 0;
                this->pressed_control = hit;
                this->triggerAction(this->SliderMove);
                this->setRepeatAction(this->SliderNoAction);
                this->setSliderDown(true);
            } else {
                opt.sliderPosition = this->highLimit;
                hit = style->hitTestComplexControl(QStyle::CC_Slider, &opt, ev->pos(), this);
                if (hit == QStyle::SC_SliderHandle) {
                    this->active_slider = 1;
                    this->pressed_control = hit;
                    this->triggerAction(this->SliderMove);
                    this->setRepeatAction(this->SliderNoAction);
                    this->setSliderDown(true);
                }
            }

            if (this->active_slider < 0) {
                this->pressed_control = QStyle::SC_SliderHandle;
                this->click_offset = this->pixelPosToRangeValue(this->pick(ev->pos()));
                this->triggerAction(this->SliderMove);
                this->setRepeatAction(this->SliderNoAction);
            }
        } else {
            ev->ignore();
        }

        QSlider::mousePressEvent(ev);
    }
    void mouseMoveEvent(QMouseEvent *ev) override {
        if (this->pressed_control != QStyle::SC_SliderHandle) {
            ev->ignore();
            return;
        }

        ev->accept();
        int new_pos = this->pixelPosToRangeValue(this->pick(ev->pos()));
        QStyleOptionSlider opt;
        this->initStyleOption(&opt);

        int offset, diff;
        if (this->active_slider < 0) {
            offset = new_pos - this->click_offset;
            this->highLimit += offset;
            this->lowLimit += offset;
            if (this->lowLimit < this->minimum()) {
                diff = this->minimum() - this->lowLimit;
                this->lowLimit += diff;
                this->highLimit += diff;
            }
            if (this->highLimit > this->maximum()) {
                diff = this->maximum() - this->highLimit;
                this->lowLimit += diff;
                this->highLimit += diff;
            }
        } else if (this->active_slider == 0) {
            if (new_pos >= this->highLimit)
                new_pos = this->highLimit - 1;
            this->lowLimit = new_pos;
        } else {
            if (new_pos <= this->lowLimit)
                new_pos = this->lowLimit + 1;
            this->highLimit = new_pos;
        }

        this->click_offset = new_pos;
        this->update();
        emit this->sliderMoved(this->lowLimit, this->highLimit);
    }

    int lowLimit, highLimit;
    inline int pick(QPoint const& pt) { return this->orientation() == Qt::Horizontal ? pt.x() : pt.y(); }
    int pixelPosToRangeValue(int pos) {
        QStyleOptionSlider opt;
        this->initStyleOption(&opt);
        QStyle* style = QApplication::style();

        QRect gr = style->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderGroove, this);
        QRect sr = style->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);

        int slider_length, slider_min, slider_max;
        if (this->orientation() == Qt::Horizontal) {
            slider_length = sr.width();
            slider_min = gr.x();
            slider_max = gr.right() - slider_length + 1;
        } else {
            slider_length = sr.height();
            slider_min = gr.y();
            slider_max = gr.bottom() - slider_length + 1;
        }

        return style->sliderValueFromPosition(this->minimum(), this->maximum(), pos-slider_min, slider_max-slider_min, opt.upsideDown);
    }
    QStyle::SubControl pressed_control = QStyle::SC_None;
    int tick_interval = 0;
    QSlider::TickPosition tick_position = QSlider::NoTicks;
    QStyle::SubControl hover_control = QStyle::SC_None;
    int click_offset = 0;
    int active_slider = 0;
};
