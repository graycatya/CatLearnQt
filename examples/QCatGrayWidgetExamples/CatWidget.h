#ifndef CATWIDGET_H
#define CATWIDGET_H

#include <QWidget>
#include <QHash>

class ListiongOptions;
class QPushButton;

namespace Ui {
class CatWidget;
}

class CatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CatWidget(QWidget *parent = nullptr);
    ~CatWidget();

private:
    void InitUi();
    void InitProperty();
    void InitConnect();

    void InitToolButtons();
    void InitToolWidgets();

    void UpdateStyle();

private slots:
    void On_ToolButtons(int);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    Ui::CatWidget *ui;
    ListiongOptions *m_pToolListiongOptions;
    QHash<QString, QPushButton*> m_pToolButtons;

};

#endif // CATWIDGET_H
