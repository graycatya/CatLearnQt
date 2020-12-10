#ifndef CATSLIDER_H
#define CATSLIDER_H

#include <QWidget>

class QPushButton;

class CatSlider : public QWidget
{
    Q_OBJECT
public:
    enum State {
        TwoSlidingBlock = 2,
        OneSlidingBlock = 1,
        NotSlidingBlock = 0
    };
    explicit CatSlider(QWidget *parent = nullptr);
    ~CatSlider();

private:
    void InitUi();
    void InitProperty();
    void InitConnect();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Qt::Orientation m_yOrientation;

    QWidget *m_pSliderBackGround;       // 滑动条背景
    QWidget *m_pSliderMoveBackGround;   // 滑动条移动背景
    QPushButton *m_pHeadSliding;        // 滑块 - 头部
    QPushButton *m_pTailSliding;        // 滑块 - 尾部

};

#endif // CATSLIDER_H
