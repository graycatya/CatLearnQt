#pragma once
#include <QMainWindow>



class CatFrameLessMainViewPrivate;

class CatFrameLessMainView : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(bool isMax READ isMax NOTIFY isMaxChanged)

public:
    explicit CatFrameLessMainView(QWidget *parent = nullptr);
    ~CatFrameLessMainView();

    void moveToScreenCenter();

    bool isMax() const;

    QWidget *titleItem() const;

    static QRect calcCenterGeo(const QRect &screenGeo, const QSize &normalSize);

    void moveUpdateSize();

#ifdef Q_OS_WIN32
    Q_INVOKABLE void setTitlecontains(bool contain);
#endif

public slots:
    void setIsMax(bool isMax);
    void setTitleItem(QWidget *item);
    void setWork(bool work);

signals:
    void isMaxChanged(bool isMax);
    void updateSize();
    void moveWindow();


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
    void resizeEvent(QResizeEvent *) override;
    void dragMoveEvent(QDragMoveEvent *event) override;

private:
    CatFrameLessMainViewPrivate *m_pCatFrameLessMainViewPrivate;
    bool m_bWork;
    QRect m_yItemSize;

};
