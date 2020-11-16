#ifndef IMAGETOOLBASE_H
#define IMAGETOOLBASE_H

#include <QWidget>

class ProcessObject;
class ButtonTool;

#define AppPath qApp->applicationDirPath()
#define STRDATETIME qPrintable (QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss"))


class ImageToolBase : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor MaskLayerColor READ GetMaskLayerColor WRITE SetMaskLayerColor)

public:
    enum STATE {CLOSE};
    explicit ImageToolBase(QWidget *parent = nullptr);
    ~ImageToolBase();

    void SetLightState(QString state);

    QColor GetMaskLayerColor( void ) const;

private:
    virtual void InitUi( void ) = 0;
    virtual void InitProperty( void ) = 0;


signals:
    void clicked(STATE);

public slots:
    void SetMaskLayerColor(QColor color);   // 设置遮罩颜色

protected:
    QWidget *m_pParent; // 父对象
    ButtonTool *m_pButtonTool; // 按钮组
    ProcessObject *m_pScreen; // 处理屏幕的对象
    QPixmap *m_pFullScreen;   // 保存的全屏背景图像
    QPixmap *m_pBackgroundScreen; // 遮罩层
    QPoint m_qMovePos; // 坐标缓存
    bool m_bLight; // 灯 - 遮罩背景
    bool m_bCut; // 切换 - 放大镜或聚光灯 区域 矩形(false), 圆形(true)
    bool m_bInit; // 初始化成功标志
    QColor MaskLayerColor;
};

#endif // IMAGETOOLBASE_H
