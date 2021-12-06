#ifndef SIDEBOXBUTTON_H
#define SIDEBOXBUTTON_H

#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>

class SideBoxButton : public QPushButton
{
    Q_OBJECT
public:
    explicit SideBoxButton(QWidget *parent = nullptr);
    ~SideBoxButton();

    void setButtonText(QString text);

    void UpdateButtonState();

    void UpdateButtonSideState(bool state);


private:
    void InitUi();
    void InitProperty();
    void InitConnect();

    void UpdateStyle();

    void SetButtonBackState(QString state);
    void SetButtonRightWidgetState(QString state);

protected:
    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);

private:
    QWidget *m_pBackWeidget;
    QHBoxLayout *m_pBackLayout;
    QLabel *m_pImageLabel;
    QLabel *m_pTextLabel;
    QWidget *m_pRigthWidget;
};

#endif // SIDEBOXBUTTON_H
