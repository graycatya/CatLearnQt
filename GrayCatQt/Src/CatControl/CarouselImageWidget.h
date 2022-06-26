#ifndef CAROUSELIMAGEWIDGET_H
#define CAROUSELIMAGEWIDGET_H

#include <QWidget>
#include <QScrollArea>
#include <QTimer>
#include <QPropertyAnimation>
#include <QPushButton>

class CarouselImageWidget : public QWidget
{
    Q_OBJECT
    Q_ENUMS(ChangeWay)
    Q_ENUMS(Direction)
public:
    enum ChangeWay {
        STATICSWITCH,
        SLIDESWITCH,
        OPACITYSWITCH
    };

    enum Direction {
        LEFT,
        RIGHT
    };
    explicit CarouselImageWidget(QWidget *parent = nullptr);
    ~CarouselImageWidget();

    void SetImageList(QStringList imageFileNameList);
    void AddImage(QString imageFileName);
    void StartPlay(int msec = 1000, int duration = 900);
    void StopPlay();

    void SetChangeWay(ChangeWay changeway);
    void SetDirection(Direction direction);
    int ImageCount();

private:
    void InitProperty();
    void InitConnect();

    void paintEvent(QPaintEvent *event);
    void paintStaticSwitch(QPainter *painter);
    void paintSlideSwitch(QPainter *painter);
    void paintOpacitySwitch(QPainter *painter);

public slots:
    void On_ImageChangeTimeout();
    void SetCurrentImageIndex(int index);

private:
    ChangeWay m_yChangeWay = STATICSWITCH;
    Direction m_yDirection = RIGHT;
    QList<QString> m_yImageFileNameList;

    QTimer *m_pImageChangeTimer = nullptr;
    int m_yCurrentDrawImageIndex = 0;

    QPixmap m_yCurrentPixmap;
    QPixmap m_yNextPixmap;

    QPropertyAnimation *m_pPropertyAnimation = nullptr;
    int AnimationDuration = 1500;
};

#endif // CAROUSELIMAGEWIDGET_H
