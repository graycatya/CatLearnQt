#include "CatFrameLessView.h"
#include <QGuiApplication>
#include <QQuickItem>
#include <QScreen>
#include <QWindow>
//#include <QDebug>


class CatFrameLessViewPrivate
{
public:
    bool m_isMax = false;
    QQuickItem *m_titleItem = nullptr;
};

CatFrameLessView::CatFrameLessView(QWindow *parent)
    : QQuickView(parent)
    , m_pCatFrameLessViewPrivate(new CatFrameLessViewPrivate)
{
    setFlags(Qt::WindowMinMaxButtonsHint | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);

    setResizeMode(SizeRootObjectToView); //添加后可自适应布局
    setColor(QColor(0, 0, 0, 0));

    setIsMax(windowState() == Qt::WindowMaximized);

    connect(this, &QWindow::windowStateChanged, this, [&](Qt::WindowState state){
        setIsMax(state == Qt::WindowMaximized);
    });
}

CatFrameLessView::~CatFrameLessView()
{
    delete m_pCatFrameLessViewPrivate;
}

void CatFrameLessView::moveToScreenCenter()
{
    auto geo = calcCenterGeo(screen()->availableGeometry(), size());
    if(minimumWidth() > geo.width() || minimumHeight() > geo.height())
    {
        setMinimumSize(geo.size());
    }

    setGeometry(geo);
    update();
}

QRect CatFrameLessView::calcCenterGeo(const QRect &screenGeo, const QSize &normalSize)
{
    // normalsize 正常大小， 屏幕位置

    int w = normalSize.width();
    int h = normalSize.height();
    int x = screenGeo.x() + (screenGeo.width() - w) / 2;
    int y = screenGeo.y() + (screenGeo.height() - h) / 2;

    //qDebug() << w << " : " << h << " : " << x << " : " << y;

    if (screenGeo.width() < w) {
        x = screenGeo.x();
        w = screenGeo.width();
    }
    if (screenGeo.height() < h) {
        y = screenGeo.y();
        h = screenGeo.height();
    }

    return {x, y, w, h };
}

bool CatFrameLessView::isMax() const
{
    return m_pCatFrameLessViewPrivate->m_isMax;
}

QQuickItem *CatFrameLessView::titleItem() const
{
    return m_pCatFrameLessViewPrivate->m_titleItem;
}

void CatFrameLessView::setIsMax(bool isMax)
{
    if(m_pCatFrameLessViewPrivate->m_isMax == isMax)
    {
        return;
    }

    m_pCatFrameLessViewPrivate->m_isMax = isMax;
    emit isMaxChanged(m_pCatFrameLessViewPrivate->m_isMax);
}

void CatFrameLessView::setTitleItem(QQuickItem *item)
{
    m_pCatFrameLessViewPrivate->m_titleItem = item;
}

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
bool CatFrameLessView::nativeEvent(const QByteArray &eventType, void *message, qintptr *result)
#else
bool CatFrameLessView::nativeEvent(const QByteArray &eventType, void *message, long *result)
#endif

{
    return QQuickView::nativeEvent(eventType, message, result);
}

void CatFrameLessView::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    emit updateSize();
    QQuickView::resizeEvent(event);
}
