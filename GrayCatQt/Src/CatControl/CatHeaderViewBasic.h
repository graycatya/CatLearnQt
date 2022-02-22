#ifndef CATHEADERVIEWBASIC_H
#define CATHEADERVIEWBASIC_H

#include <QHeaderView>

class CatHeaderViewBasic : public QHeaderView
{
    Q_OBJECT
public:
    enum VIEWSTATE {
        CHECKBOX,
    };
    explicit CatHeaderViewBasic(Qt::Orientation orientation, QWidget * parent = 0);
    ~CatHeaderViewBasic();

protected:
    bool eventFilter(QObject *object, QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const override;

    QRect sectionRect(int logicalIndex) const;
    QRect buttonMenuRect(int logicalIndex) const;
    QRect prevRect(int logicalIndex) const;
    QRect nextRect(int logicalIndex) const;

private:


};

#endif // CATHEADERVIEWBASIC_H
