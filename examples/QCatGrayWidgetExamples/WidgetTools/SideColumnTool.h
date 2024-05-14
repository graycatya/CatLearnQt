#ifndef SIDECOLUMNTOOL_H
#define SIDECOLUMNTOOL_H

#include <QWidget>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QButtonGroup>
#include "SideWidgetTools/SideBoxButton.h"

namespace Ui {
class SideColumnTool;
}

class SideColumnTool : public QWidget
{
    Q_OBJECT

public:
    explicit SideColumnTool(QWidget *parent = nullptr);
    ~SideColumnTool();

private:
    void InitUi();
    void InitProperty();
    void InitConnect();

    void UpdateStyle();

    void InitDefauleSlider();

    void SetUnfold(bool unfold);
    void SetSideButtonState(QString state);

protected:
    void resizeEvent(QResizeEvent *event);
    void showEvent(QShowEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::SideColumnTool *ui;
    QPushButton *m_pSideButton;
    bool m_bUnfold;

    QButtonGroup *m_pSideButtonGroup;
    QVector<SideBoxButton*> m_pSideButtons;
    //QPropertyAnimation *m_pSideAnimation;
};

#endif // SIDECOLUMNTOOL_H
