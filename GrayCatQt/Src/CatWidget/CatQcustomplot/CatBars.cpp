#include "CatBars.h"

#include <QString>

CatBars::CatBars(QCPAxis *keyAxis, QCPAxis *valueAxis)
     : QCPBars(keyAxis, valueAxis),
     mTextAlignment(Qt::AlignCenter),
     mSpacing(5),
     mFont(QFont(QLatin1String("Ubuntu"), 12)),
     m_bShowText(false)
{

}

CatBars::~CatBars()
{

}

void CatBars::setTextAlignment(Qt::Alignment alignment)
{
    mTextAlignment = alignment;
}

void CatBars::setSpacing(double spacing)
{
    mSpacing = spacing;
}

void CatBars::setFont(const QFont &font)
{
    mFont = font;
}

void CatBars::SetShowText(bool show)
{
    m_bShowText = show;
}

void CatBars::drawText(QCPPainter *painter, const QRectF &rect, double value)
{
    // 计算文字的位置
    painter->setFont(mFont);                     // 设置字体
    QString text = QString::number(value, 'g', 2);   // 取得当前value轴的值，保留两位精度

    QRectF textRect = painter->fontMetrics().boundingRect(0, 0, 0, 0, Qt::TextDontClip | mTextAlignment, text);  // 计算文字所占用的大小

    if (mKeyAxis.data()->orientation() == Qt::Horizontal) {    // 当key轴为水平轴的时候
        if (mKeyAxis.data()->axisType() == QCPAxis::atTop)     // 上轴，移动文字到柱状图下面
            textRect.moveTopLeft(rect.bottomLeft() + QPointF(0, mSpacing));
        else                                                   // 下轴，移动文字到柱状图上面
            textRect.moveBottomLeft(rect.topLeft() - QPointF(0, mSpacing));
        textRect.setWidth(rect.width());
        painter->drawText(textRect, Qt::TextDontClip | mTextAlignment, text);
    } else {                                                  // 当key轴为竖直轴的时候
        if (mKeyAxis.data()->axisType() == QCPAxis::atLeft)   // 左轴，移动文字到柱状图右边
            textRect.moveTopLeft(rect.topRight() + QPointF(mSpacing, 0));
        else                                                  // 右轴，移动文字到柱状图左边
            textRect.moveTopRight(rect.topLeft() - QPointF(mSpacing, 0));
        textRect.setHeight(rect.height());
        painter->drawText(textRect, Qt::TextDontClip | mTextAlignment, text);
    }
}

void CatBars::draw(QCPPainter *painter)
{
    if (!mKeyAxis || !mValueAxis) { qDebug() << Q_FUNC_INFO << "invalid key or value axis"; return; }
    if (mDataContainer->isEmpty()) return;
    m_pRects.clear();
    QCPBarsDataContainer::const_iterator visibleBegin, visibleEnd;
    getVisibleDataBounds(visibleBegin, visibleEnd);

    // loop over and draw segments of unselected/selected data:
    QList<QCPDataRange> selectedSegments, unselectedSegments, allSegments;
    getDataSegments(selectedSegments, unselectedSegments);
    allSegments << unselectedSegments << selectedSegments;
    for (int i=0; i<allSegments.size(); ++i)
    {
      bool isSelectedSegment = i >= unselectedSegments.size();
      QCPBarsDataContainer::const_iterator begin = visibleBegin;
      QCPBarsDataContainer::const_iterator end = visibleEnd;
      mDataContainer->limitIteratorsToDataRange(begin, end, allSegments.at(i));
      if (begin == end)
        continue;

      for (QCPBarsDataContainer::const_iterator it=begin; it!=end; ++it)
      {
        // check data validity if flag set:
  #ifdef QCUSTOMPLOT_CHECK_DATA
        if (QCP::isInvalidData(it->key, it->value))
          qDebug() << Q_FUNC_INFO << "Data point at" << it->key << "of drawn range invalid." << "Plottable name:" << name();
  #endif
        // draw bar:
        if (isSelectedSegment && mSelectionDecorator)
        {
          mSelectionDecorator->applyBrush(painter);
          mSelectionDecorator->applyPen(painter);
        } else
        {
          painter->setBrush(mBrush);
          painter->setPen(mPen);
        }
        applyDefaultAntialiasingHint(painter);
        CatBarsRectData datas;
        datas.rect = getBarRect(it->key, it->value);
        datas.key = it->key;
        datas.value = it->value;
        m_pRects.push_back(datas);
        painter->drawPolygon(getBarRect(it->key, it->value));
        if(m_bShowText)
        {
            this->drawText(painter, getBarRect(it->key, it->value), it->value);
        }
      }
    }

    // draw other selection decoration that isn't just line/scatter pens and brushes:
    if (mSelectionDecorator)
      mSelectionDecorator->drawDecoration(painter, selection());
}


