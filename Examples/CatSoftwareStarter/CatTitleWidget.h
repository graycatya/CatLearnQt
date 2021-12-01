#ifndef CATTITLEWIDGET_H
#define CATTITLEWIDGET_H

#include <QLabel>

class CatTitleWidget : public QLabel
{
    Q_OBJECT
public:
    explicit CatTitleWidget(QWidget *parent = nullptr);
    ~CatTitleWidget();

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);

signals:
    void doubleClick();

private:

};

#endif // CATTITLEWIDGET_H
