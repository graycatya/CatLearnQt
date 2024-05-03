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
    void InitBoardTool();

    void UpdateStyle();

protected:
    /*重写 事件，防止win下继承父对象后事件继承问题*/
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void showEvent(QShowEvent *) override;
    void resizeEvent(QResizeEvent *event) override;
    void moveEvent(QMoveEvent *event) override;
protected:
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
    void enterEvent(QEnterEvent *event) override;
#else
    void enterEvent(QEvent *event) override;
#endif
    void leaveEvent(QEvent *event) override;

private:
    Ui::CatDrawingBoard *ui;
    ListiongOptions *m_pTeachingOptions;
    ListiongOptions *m_pBoardOptions;
    QHash<QString, QPushButton*> m_pTeachingButtons;
    QHash<QString, QPushButton*> m_pBoardButtons;
    QVector<CatGraphicsScene*> m_pBoardScenes;
};

#endif // CATDRAWINGBOARD_H
