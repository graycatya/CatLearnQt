#include "CarouselImageWidget.h"
#include <QPainter>
#include <QDebug>

CarouselImageWidget::CarouselImageWidget(QWidget *parent)
    : QWidget(parent)
    , m_yCurrentDrawImageIndex(0)
{
    InitProperty();
    InitConnect();
}

CarouselImageWidget::~CarouselImageWidget()
{
    if(m_pImageChangeTimer->isActive())
    {
        m_pImageChangeTimer->stop();
        delete m_pImageChangeTimer;
        m_pImageChangeTimer = nullptr;
    }
}

void CarouselImageWidget::SetImageList(QStringList imageFileNameList)
{
    m_yImageFileNameList = imageFileNameList;
}

void CarouselImageWidget::AddImage(QString imageFileName)
{
    m_yImageFileNameList.append(imageFileName);
}

void CarouselImageWidget::StartPlay(int msec, int duration)
{
    if(!m_yImageFileNameList.isEmpty() && !m_pImageChangeTimer->isActive())
    {
        if(duration >= msec)
        {
            duration = duration - duration * 0.1;
        }
        AnimationDuration = duration;
        m_yCurrentDrawImageIndex = 0;
        m_yCurrentPixmap = QPixmap(m_yImageFileNameList.at(m_yCurrentDrawImageIndex));
        m_yNextPixmap = QPixmap(m_yImageFileNameList.at(m_yCurrentDrawImageIndex));
        m_pPropertyAnimation->setDuration(AnimationDuration);
        m_pImageChangeTimer->start(msec);
        this->update();
    }
}

void CarouselImageWidget::StopPlay()
{
    if(m_pImageChangeTimer->isActive())
    {
        m_yCurrentDrawImageIndex = 0;
        m_pImageChangeTimer->stop();
    }
}

void CarouselImageWidget::SetChangeWay(ChangeWay changeway)
{
    m_yChangeWay = changeway;
    this->update();
}

void CarouselImageWidget::SetDirection(Direction direction)
{
    m_yDirection = direction;
    this->update();
}

int CarouselImageWidget::ImageCount()
{
    return m_yImageFileNameList.size();
}

void CarouselImageWidget::InitProperty()
{
    // 图片渐变属性
    this->setProperty("ImageChange", 1.0);
    m_pPropertyAnimation = new QPropertyAnimation(this, "ImageChange");
    m_pPropertyAnimation->setStartValue(1.0);
    m_pPropertyAnimation->setEndValue(0.0);


    m_pImageChangeTimer = new QTimer(this);

}

void CarouselImageWidget::InitConnect()
{
    connect(m_pPropertyAnimation, SIGNAL(valueChanged(const QVariant&)), this, SLOT(update()));
    connect(m_pImageChangeTimer, &QTimer::timeout, this, &CarouselImageWidget::On_ImageChangeTimeout);
}

void CarouselImageWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    switch (m_yChangeWay) {
        case STATICSWITCH: {
            paintStaticSwitch(&painter);
            break;
        }
        case SLIDESWITCH: {
            paintSlideSwitch(&painter);
            break;
        }
        case OPACITYSWITCH: {
            paintOpacitySwitch(&painter);
            break;
        }
    }

}

void CarouselImageWidget::paintStaticSwitch(QPainter *painter)
{
    QRect imageRect = this->rect();
    if(!m_yImageFileNameList.isEmpty())
    {
        if(m_yImageFileNameList.count() == 1)
        {
            QPixmap backPixmap = QPixmap(m_yImageFileNameList.first());
            painter->drawPixmap(imageRect, backPixmap.scaled(imageRect.size()));
        } else if(m_yImageFileNameList.count() > 1)
        {
            painter->setOpacity(1);
            painter->drawPixmap(imageRect, m_yNextPixmap.scaled(imageRect.size()));
            painter->setOpacity(0);
            painter->drawPixmap(imageRect, m_yCurrentPixmap.scaled(imageRect.size()));
        }
    }
}

void CarouselImageWidget::paintSlideSwitch(QPainter *painter)
{
    QRect imageRect = this->rect();
    if(!m_yImageFileNameList.isEmpty())
    {
        if(m_yImageFileNameList.count() == 1)
        {
            QPixmap backPixmap = QPixmap(m_yImageFileNameList.first());
            painter->drawPixmap(imageRect, backPixmap.scaled(imageRect.size()));
        } else if(m_yImageFileNameList.count() > 1)
        {
            qDebug() << this->property("ImageChange").toFloat();
            float imageChangeOpacity = this->property("ImageChange").toFloat();
            float offset = (imageChangeOpacity * width()) / 1.0;
            if(m_yDirection == Direction::RIGHT)
            {
                painter->drawPixmap(offset, 0, m_yNextPixmap.scaled(imageRect.size()));
                painter->drawPixmap(offset - width(), 0, m_yCurrentPixmap.scaled(imageRect.size()));
            } else {
                painter->drawPixmap(offset - width(), 0, m_yNextPixmap.scaled(imageRect.size()));
                painter->drawPixmap(offset, 0, m_yCurrentPixmap.scaled(imageRect.size()));
            }
        }
    }
}

void CarouselImageWidget::paintOpacitySwitch(QPainter *painter)
{
    QRect imageRect = this->rect();
    if(!m_yImageFileNameList.isEmpty())
    {
        if(m_yImageFileNameList.count() == 1)
        {
            QPixmap backPixmap = QPixmap(m_yImageFileNameList.first());
            painter->drawPixmap(imageRect, backPixmap.scaled(imageRect.size()));
        } else if(m_yImageFileNameList.count() > 1)
        {
            float imageChangeOpacity = this->property("ImageChange").toFloat();
            painter->setOpacity(1);
            painter->drawPixmap(imageRect, m_yNextPixmap.scaled(imageRect.size()));
            painter->setOpacity(imageChangeOpacity);
            painter->drawPixmap(imageRect, m_yCurrentPixmap.scaled(imageRect.size()));
        }
    }
}

void CarouselImageWidget::On_ImageChangeTimeout()
{
    m_yCurrentPixmap = QPixmap(m_yImageFileNameList.at(m_yCurrentDrawImageIndex));

    if(m_yDirection == LEFT)
    {
        m_yCurrentDrawImageIndex--;
    } else if(m_yDirection == RIGHT)
    {
        m_yCurrentDrawImageIndex++;
    }

    if (m_yCurrentDrawImageIndex >= m_yImageFileNameList.count())
    {
        m_yCurrentDrawImageIndex = 0;
    } else if(m_yCurrentDrawImageIndex < 0)
    {
        m_yCurrentDrawImageIndex = m_yImageFileNameList.count()-1;
    }
    m_pPropertyAnimation->setDuration(AnimationDuration);

    m_yNextPixmap = QPixmap(m_yImageFileNameList.at(m_yCurrentDrawImageIndex));

    // 动画类重新开始;
    m_pPropertyAnimation->start();
}

void CarouselImageWidget::SetCurrentImageIndex(int index)
{
    if(!m_yImageFileNameList.isEmpty())
    {
        m_yCurrentPixmap = QPixmap(m_yImageFileNameList.at(m_yCurrentDrawImageIndex));
        m_yCurrentDrawImageIndex = index;
        if(m_yImageFileNameList.isEmpty())
        {
            m_yCurrentDrawImageIndex = 0;
        } else {
            if(m_yCurrentDrawImageIndex < 0)
            {
                m_yCurrentDrawImageIndex = 0;
            } else if(m_yCurrentDrawImageIndex >= m_yImageFileNameList.size())
            {
                m_yCurrentDrawImageIndex = m_yImageFileNameList.size() - 1;
            }
        }

        m_yNextPixmap = QPixmap(m_yImageFileNameList.at(m_yCurrentDrawImageIndex));
    }
}




