#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QButtonGroup>

class ListiongOptions : public QWidget
{
    Q_OBJECT
public:
    explicit ListiongOptions(QWidget *parent = nullptr);
    ~ListiongOptions();

public:
    void AddButton(QPushButton *button);
    void AddItem(QSpacerItem *item);
    QWidget *GetRootWidget( void ) const;
    QButtonGroup *GetButtonGroup( void ) const;
    void Clear();

private:
    void InitUi( void );
    void InitProperty( void );

protected:
    void showEvent(QShowEvent *event);

private:
    QVBoxLayout *m_pRootLayout;
    QWidget *m_pRootWidget;
    QVBoxLayout *m_pRootWidgetLayout;
    QList<QPushButton*> m_lButtonList;
    QList<QSpacerItem*> m_lItemList;
    QButtonGroup *m_pButtonGroup;

};

