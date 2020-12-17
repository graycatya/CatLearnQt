#ifndef CATAXISTAG_H
#define CATAXISTAG_H

#include <QObject>
#include "qcustomplot.h"


class CatAxisTag : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPen Pen READ GetPen WRITE SetPen)
    Q_PROPERTY(QBrush LabelBrush READ GetLabelBrush WRITE SetLabelBrush)
    Q_PROPERTY(QString LabelText READ GetLabelText WRITE SetLabelText)
public:
    explicit CatAxisTag(QCPAxis *parent = nullptr);
    ~CatAxisTag();

    QPen GetPen() const { return mLabel->pen(); }
    QBrush GetLabelBrush() const { return mLabel->brush(); }
    QString GetLabelText() const { return mLabel->text(); }

    void UpdatePosition(double value);

private:
    void InitUi();
    void InitProperty();

public slots:
    void SetPen(const QPen& pen);
    void SetLabelBrush(const QBrush& brush);
    void SetLabelText(const QString& text);



protected:
    QCPAxis *m_pAxis;
    QPointer<QCPItemTracer> mDummyTracer;
    QPointer<QCPItemLine> mArrow;
    QPointer<QCPItemText> mLabel;

};

#endif // CATAXISTAG_H
