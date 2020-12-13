#pragma once

#include <QWidget>


class QScrollArea;
class QPushButton;
class QSpacerItem;
class QButtonGroup;
class QVBoxLayout;
class QHBoxLayout;

class ListiongOptions : public QWidget
{
    Q_OBJECT
public:
    enum LAYOUT {
        VBox,
        HBox
    };
    explicit ListiongOptions(LAYOUT layout, QWidget *parent = nullptr);
    ~ListiongOptions();

public:
    void AddButton(QPushButton *button, int id);
    void AddButtonNoGroup(QPushButton *button);
    void AddWidget(QWidget *widget);
    void AddItem(QSpacerItem *item);
    QWidget *GetRootWidget( void ) const;
    QButtonGroup *GetButtonGroup( void ) const;
    void Clear();
    void *GetButtonlayout( void );

private:
    void InitUi( void );
    void InitProperty( void );

protected:
    bool eventFilter(QObject *watched, QEvent *event);
    void showEvent(QShowEvent *event);

private:
    QVBoxLayout *m_pRootLayout;
    QWidget *m_pRootWidget;
    QVBoxLayout *m_pRootWidgetLayout;
    QScrollArea *m_pScrollArea;
    QWidget *m_pButtonLists;
    QHBoxLayout *m_pHboxLayoutButton;
    void *m_pButtonListsLayout;
    QList<QPushButton*> m_lButtonList;
    QList<QSpacerItem*> m_lItemList;
    QButtonGroup *m_pButtonGroup;
    LAYOUT m_yLayout;
};

