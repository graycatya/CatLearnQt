#ifndef CATGRAYQUICKWIDGET_H
#define CATGRAYQUICKWIDGET_H

#include <QWidget>
#include <QHash>

class QCatGrayListingOptions;
class QPushButton;

class CatGrayQuickWidgetTest;

namespace Ui {
class CatGrayQuickWidget;
}

class CatGrayQuickWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CatGrayQuickWidget(QWidget *parent = nullptr);
    ~CatGrayQuickWidget();

private:
    void InitUi();
    void InitProperty();
    void InitConnect();

    void InitToolButtons();
    void InitToolWidgets();

    void UpdateStyle();

private slots:
    void On_ToolButtons(int);

private:
    Ui::CatGrayQuickWidget *ui;
    QCatGrayListingOptions *m_pToolListiongOptions;
    QHash<QString, QPushButton*> m_pToolButtons;
    CatGrayQuickWidgetTest *m_pCatGrayQuickWidgetTest;
};

#endif // CATGRAYQUICKWIDGET_H
