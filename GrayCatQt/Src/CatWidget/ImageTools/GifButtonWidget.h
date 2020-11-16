#ifndef GIFBUTTONWIDGET_H
#define GIFBUTTONWIDGET_H

#include <QWidget>

struct GifWriter;

class QAction;
class QMenu;

namespace Ui {
class GifButtonWidget;
}

class GifButtonWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GifButtonWidget(QWidget *parent = nullptr);
    ~GifButtonWidget();

    void SetGifSelect(bool select);
    void SetMoveState(QString state);
    void SetVideoState(QString state);
    void SetShowState(QString state);

private:
    void InitProperty( void );
    void ReadOnly(bool only);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void showEvent(QShowEvent *event) override;

signals:
    void gifmoveed(bool);
    void gifstarted(bool);
    void gifshowed(bool);
    void gifgeometryed(int, int, int, int);
    void closeed();
    void abouted();

public slots:
    void On_Gifgeometry(int, int, int, int);

private:
    Ui::GifButtonWidget *ui;
    bool m_bGifselect;
    bool m_bGifStart;
    bool m_bGifMove;
    bool m_bGifShow;

    bool m_bShowFunction;
    bool m_bWidgetMove;
    QPoint m_pPressPos;
    QRect m_pGifWindow;         // 录制区域
    int m_iCount;               // 帧数计数
    QString fileName;           // 保存文件名称
    QTimer *m_pVidoTimer;       // 录制定时器
    GifWriter *m_pGifWriter;

    QMenu *m_pMenu;
    QAction *m_pClose;
    QAction *m_pAbout;

};

#endif // GIFBUTTONWIDGET_H
