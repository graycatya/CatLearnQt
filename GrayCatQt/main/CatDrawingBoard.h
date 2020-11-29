#ifndef CATDRAWINGBOARD_H
#define CATDRAWINGBOARD_H

#include <QWidget>

class CatGraphicsScene;
class CatGraphicsView;
class ListiongOptions;
class QPushButton;

namespace Ui {
class CatDrawingBoard;
}

class CatDrawingBoard : public QWidget
{
    Q_OBJECT

public:
    explicit CatDrawingBoard(QWidget *parent = nullptr);
    ~CatDrawingBoard();

public:
    CatGraphicsView* CreateBoard( void );

private:
    void InitUi();
    void InitProperty();
    void InitConnect();

    void InitTeachingTool();

private:
    Ui::CatDrawingBoard *ui;
    ListiongOptions *m_pTeachingOptions;
    ListiongOptions *m_pBoardOptions;
    QHash<QString, QPushButton*> m_pTeachingButtons;
    QVector<CatGraphicsScene*> m_pBoardScenes;
};

#endif // CATDRAWINGBOARD_H
