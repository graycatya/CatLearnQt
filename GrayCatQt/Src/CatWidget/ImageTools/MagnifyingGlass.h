#ifndef MAGNIFYINGGLASS_H
#define MAGNIFYINGGLASS_H
#include "ImageToolBase.h"

class MagnifyingGlass : public ImageToolBase
{
    Q_OBJECT
public:
    explicit MagnifyingGlass(QWidget *parent = nullptr);
    ~MagnifyingGlass();

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
    qreal m_qZoomRatio;
};

#endif // MAGNIFYINGGLASS_H
