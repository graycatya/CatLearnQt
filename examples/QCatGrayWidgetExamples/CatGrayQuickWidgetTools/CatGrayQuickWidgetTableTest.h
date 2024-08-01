#ifndef CATGRAYQUICKWIDGETTABLETEST_H
#define CATGRAYQUICKWIDGETTABLETEST_H

#include <QWidget>

class QCatGrayQuickWidget;

class CatGrayQuickWidgetTableTest : public QWidget
{
    Q_OBJECT

public:
    explicit CatGrayQuickWidgetTableTest(QWidget *parent = nullptr);
    ~CatGrayQuickWidgetTableTest();

private:
    void InitUi();
    void InitProperty();
    void InitConnect();

    void UpdateStyle();

signals:
    void updateStyleed(int);

private:
    QCatGrayQuickWidget *m_pCatGrayQuickWidget;
};

#endif
