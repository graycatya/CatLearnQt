#ifndef SHADOWWIDGET_H
#define SHADOWWIDGET_H

#include <QWidget>

class CatShadowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CatShadowWidget(QWidget *widget);
    ~CatShadowWidget();

public slots:
    void SetShadowColor(QColor color);
    void SetShadowWeight(int weight);
    void SetShadowRadius(int radius);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    // 阴影属性
    QColor ShadowColor;
    int ShadowWeight = 0;
    int ShadowRadius = 0;

};

#endif // SHADOWWIDGET_H
