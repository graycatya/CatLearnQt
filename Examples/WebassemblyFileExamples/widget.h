#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_OpenFileButton_clicked();

    void on_SaveFileButton_clicked();

private:
    Ui::Widget *ui;
    QImage *image;
};
#endif // WIDGET_H
