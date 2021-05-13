#pragma once
#include <QQuickView>

/*
 * 原作者武威涛哥: https://www.zhihu.com/people/JaredTao/posts
*/

/*
 *  windos平台支持拖动和改变大小，支持Aero效果，无边框窗口，用来实现自定义标题蓝
 *  非windows平台,不做其他处理，由Qml模拟resize和拖动
 *  该模块使用后解决了，QQuickView以Rectangle，Item作为根节点时候的动态布局失效问题。
 */

class CatFrameLessViewPrivate;

class CatFrameLessView : public QQuickView
{
    Q_OBJECT
    Q_PROPERTY(bool isMax READ isMax NOTIFY isMaxChanged)
public:
    explicit CatFrameLessView(QWindow *parent = nullptr);
    ~CatFrameLessView();

    void moveToScreenCenter();

    bool isMax() const;

    QQuickItem *titleItem() const;

    static QRect calcCenterGeo(const QRect &screenGeo, const QSize &normalSize);

public slots:
    void setIsMax(bool isMax);
    void setTitleItem(QQuickItem *item);

signals:
    void isMaxChanged(bool isMax);

protected:
/*
 * 重写此操作以处理平台相关事件。将被给出eventType, message和result。
 * 这可能会使您的应用程序不可移植。
 * 仅当事件被处理时才返回true。
*/
#    if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    bool nativeEvent(const QByteArray &eventType, void *message, qintptr *result) override;
#    else
    bool nativeEvent(const QByteArray &eventType, void *message, long *result) override;
#    endif

private:
    CatFrameLessViewPrivate *m_pCatFrameLessViewPrivate;

};
