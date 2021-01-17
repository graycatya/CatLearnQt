#ifndef CATQUICKWIDGET_H
#define CATQUICKWIDGET_H

#include <QWidget>

class ListiongOptions;
class QPushButton;

class QuickSliders;
class QuickQrenCode;

namespace Ui {
class CatQuickWidget;
}

class CatQuickWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CatQuickWidget(QWidget *parent = nullptr);
    ~CatQuickWidget();

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
    Ui::CatQuickWidget *ui;
    ListiongOptions *m_pToolListiongOptions;
    QHash<QString, QPushButton*> m_pToolButtons;
    QuickSliders *m_pQuickSliders;
    QuickQrenCode *m_pQuickQrenCode;

};

#endif // CATQUICKWIDGET_H
