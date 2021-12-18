#include "CatFrameLessMainView.h"
#include <QGuiApplication>
#include <QWidget>
#include <QScreen>

class CatFrameLessMainViewPrivate
{
public:
    bool m_isMax = false;
    QWidget *m_titleItem = nullptr;
};

CatFrameLessMainView::CatFrameLessMainView(QWidget *parent)
    : QMainWindow(parent)
    , m_pCatFrameLessMainViewPrivate(new CatFrameLessMainViewPrivate)
{
    setWindowFlags(Qt::WindowMinMaxButtonsHint | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);
    //setFlags(Qt::WindowMinMaxButtonsHint | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);

    //setResizeMode(SizeRootObjectToView); //添加后可自适应布局
    //setColor(QColor(0, 0, 0, 0));

    setIsMax(windowState() == Qt::WindowMaximized);

    //connect(this, &QMainWindow::windowTitleChanged);
    /*
    connect(this, &QMainWindow::windowStateChanged, this, [&](Qt::WindowState state){
        setIsMax(state == Qt::WindowMaximized);
    });
    */
}

CatFrameLessMainView::~CatFrameLessMainView()
{
    delete m_pCatFrameLessMainViewPrivate;
}

void CatFrameLessMainView::moveToScreenCenter()
{
    auto geo = calcCenterGeo(screen()->availableGeometry(), size());
    if(minimumWidth() > geo.width() || minimumHeight() > geo.height())
    {
        setMinimumSize(geo.size());
    }

    setGeometry(geo);
    update();
}

QRect CatFrameLessMainView::calcCenterGeo(const QRect &screenGeo, const QSize &normalSize)
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

    return { x, y, w, h };
}

bool CatFrameLessMainView::isMax() const
{
    return m_pCatFrameLessMainViewPrivate->m_isMax;
}

void CatFrameLessMainView::setWork(bool work)
{
    m_bWork = work;
}

QWidget *CatFrameLessMainView::titleItem() const
{
    return m_pCatFrameLessMainViewPrivate->m_titleItem;
}

void CatFrameLessMainView::setIsMax(bool isMax)
{

    if(m_pCatFrameLessMainViewPrivate->m_isMax == isMax)
    {
        return;
    }

    m_pCatFrameLessMainViewPrivate->m_isMax = isMax;
    emit isMaxChanged(m_pCatFrameLessMainViewPrivate->m_isMax);
}

void CatFrameLessMainView::setTitleItem(QWidget *item)
{
    m_pCatFrameLessMainViewPrivate->m_titleItem = item;
}

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
bool CatFrameLessMainView::nativeEvent(const QByteArray &eventType, void *message, qintptr *result)
#else
bool CatFrameLessMainView::nativeEvent(const QByteArray &eventType, void *message, long *result)
#endif

{
    return QMainWindow::nativeEvent(eventType, message, result);
}

void CatFrameLessMainView::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    emit updateSize();
    this->resize(this->geometry().size());
    QMainWindow::resizeEvent(event);
}

void CatFrameLessMainView::dragMoveEvent(QDragMoveEvent *event)
{

}


void CatFrameLessMainView::moveUpdateSize()
{
    emit moveWindow();
}
