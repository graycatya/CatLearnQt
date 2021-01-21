#ifndef CATBARS_H
#define CATBARS_H

#include "qcustomplot.h"

struct CatBarsRectData {
  QRectF rect;
  double key;
  double value;
};
class CatBars : public QCPBars
{
    Q_OBJECT
public:
    explicit CatBars(QCPAxis *keyAxis, QCPAxis *valueAxis);
    ~CatBars();

    Qt::Alignment textAligment() const { return mTextAlignment; }
    double spacing() const { return mSpacing; }
    QFont font() const { return mFont; }

    void setTextAlignment(Qt::Alignment alignment);
    void setSpacing(double spacing);
    void setFont(const QFont &font);

    void SetShowText(bool show);

    QVector<CatBarsRectData> CurrentShowRectDatass( void ) const { return m_pRects; };

private:
    void drawText(QCPPainter *painter, const QRectF &rect, double value);

protected:
    virtual void draw(QCPPainter *painter) Q_DECL_OVERRIDE;

protected:
    Qt::Alignment mTextAlignment;   // 文字对齐方式
    double mSpacing;                // 文字与柱状图的间距，这里按像素大小
    QFont mFont;                    // 文字使用的字体
    QVector<CatBarsRectData> m_pRects;       // current show rect


private:
    bool m_bShowText;

};

#endif // CATBARS_H
