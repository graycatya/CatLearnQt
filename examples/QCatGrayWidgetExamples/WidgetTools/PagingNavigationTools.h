#ifndef PAGINGNAVIGATIONTOOLS_H
#define PAGINGNAVIGATIONTOOLS_H

#include <QWidget>

class QCatGrayIntValidator;

namespace Ui {
class PagingNavigationTools;
}

class PagingNavigationTools : public QWidget
{
    Q_OBJECT

public:
    explicit PagingNavigationTools(QWidget *parent = nullptr);
    ~PagingNavigationTools();

private slots:
    void on_InitPagingNavigationButton_clicked();

    void on_UpdatePagingNavigationButton_clicked();

    void on_SetCurrentPageButton_clicked();

protected:
    void changeEvent(QEvent *event);

private:
    void InitUi();
    void InitProperty();
    void InitConnect();

    void UpdateStyle();

private:
    Ui::PagingNavigationTools *ui;
    QCatGrayIntValidator *currentpageval;
};

#endif // PAGINGNAVIGATIONTOOLS_H
