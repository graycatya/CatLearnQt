#ifndef CATGRAYQUICKWIDGETTEST_H
#define CATGRAYQUICKWIDGETTEST_H


#include <QWidget>

class QCatGrayQuickWidget;

class CatGrayQuickWidgetTest : public QWidget
{
    Q_OBJECT

public:
    explicit CatGrayQuickWidgetTest(QWidget *parent = nullptr);
    ~CatGrayQuickWidgetTest();

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
