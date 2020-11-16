#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H
#include "ImageToolBase.h"

class SpotLight : public ImageToolBase
{
    Q_OBJECT
public:
    explicit SpotLight(QWidget *parent = nullptr);
    ~SpotLight();

public:

private:
    void InitUi() override;
    void InitProperty() override;

    bool ZoomIsInArea(QPoint pos);

protected:
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void paintEvent(QPaintEvent *) override;
    void showEvent(QShowEvent *) override;

private:
    QWidget *m_pZoom;

};

#endif // SPOTLIGHT_H
