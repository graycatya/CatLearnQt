#include "GifButtonWidget.h"
#include "ui_GifButtonWidget.h"
#include <QFile>
#include <QMouseEvent>
#include <QDebug>
#include <QTimer>
#include <QScreen>
#include <QFileDialog>
#include <QMenu>
#include <QAction>
#include "gif.h"
#include <QRegExp>
#include <QRegExpValidator>


GifButtonWidget::GifButtonWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GifButtonWidget),
    m_bGifselect(false),
    m_bGifStart(false),
    m_bGifMove(true),
    m_bGifShow(true),
    m_bShowFunction(true),
    m_bWidgetMove(false),
    m_pGifWindow(0,0,0,0),
    m_iCount(0),
    m_pVidoTimer(nullptr),
    m_pGifWriter(nullptr),
    m_pMenu(nullptr),
    m_pClose(nullptr)
{
    ui->setupUi(this);
    InitProperty();
}

GifButtonWidget::~GifButtonWidget()
{
    if(m_pVidoTimer->isActive())
    {
        m_pVidoTimer->stop();
        m_pVidoTimer->deleteLater();
        m_pVidoTimer = nullptr;
    }
    if(m_pGifWriter)
    {
        GifEnd(m_pGifWriter);
        delete m_pGifWriter;
        m_pGifWriter = nullptr;
    }
    delete ui;
}

void GifButtonWidget::SetGifSelect(bool select)
{
    m_bGifselect = select;
}

void GifButtonWidget::SetMoveState(QString state)
{
    ui->MoveButton->setProperty("State", state);
    ui->MoveButton->setStyle(QApplication::style());
}

void GifButtonWidget::SetVideoState(QString state)
{
    ui->VideoButton->setProperty("State", state);
    ui->VideoButton->setStyle(QApplication::style());
}

void GifButtonWidget::SetShowState(QString state)
{
    ui->ShowButton->setProperty("State", state);
    ui->ShowButton->setStyle(QApplication::style());
}

void GifButtonWidget::InitProperty()
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAutoFillBackground(true);
    QPalette pal = palette();
    pal.setColor(QPalette::Window,Qt::transparent);
    setPalette(pal);
    setWindowOpacity(1);
    setAttribute(Qt::WA_TranslucentBackground);

    fileName.clear();
    m_pVidoTimer = new QTimer(this);
    m_pVidoTimer->setInterval(100);

    m_pMenu = new QMenu(this);
    //m_pAbout = new QAction(this);
    //m_pAbout->setText("关于");
    //m_pMenu->addAction(m_pAbout);
    m_pClose = new QAction(this);
    m_pClose->setText("关闭");
    m_pMenu->addAction(m_pClose);

#if (QT_VERSION < QT_VERSION_CHECK(6,0,0))
    QRegExp rx("0|[1-9]\\d{0,3}");
    QRegExpValidator v(rx, this);
    ui->LineEditX->setValidator(new QRegExpValidator(rx));
    ui->LineEditY->setValidator(new QRegExpValidator(rx));
    ui->LineEditWidth->setValidator(new QRegExpValidator(rx));
    ui->LineEditHeight->setValidator(new QRegExpValidator(rx));
#else

#endif

    QFile resourceqss(":/ImageTools/qss/GifButtonWidget.css");
    resourceqss.open(QFile::ReadOnly);
    ui->RootWidget->setStyleSheet(resourceqss.readAll());
    resourceqss.close();

    ui->FrameNum->setText("");

    connect(ui->VideoButton, &QPushButton::clicked, this, [=](){
        if(!m_bGifStart)
        {
            fileName = QFileDialog::getSaveFileName(this, "选择保存位置", qApp->applicationDirPath() + "/", "gif图片(*.gif)");
            if (fileName.isEmpty()) {
                return;
            }
            if(m_pGifWriter == nullptr)
            {
                m_pGifWriter = new GifWriter;
                GifBegin(m_pGifWriter, fileName.toLocal8Bit().data(), m_pGifWindow.width(), m_pGifWindow.height(), ui->SpinBoxFps->text().toInt());
            }
            m_iCount = 0;
            SetVideoState("VideoStart");
            m_pVidoTimer->start(1000 / ui->SpinBoxFps->text().toInt());
        } else {
            if(m_pVidoTimer->isActive())
            {
                m_pVidoTimer->stop();
            }
            if(m_pGifWriter)
            {
                GifEnd(m_pGifWriter);
                delete m_pGifWriter;
                m_pGifWriter = nullptr;
            }
            m_iCount = 0;
            fileName.clear();
            SetVideoState("VideoStop");
        }
        m_bGifStart = !m_bGifStart;
        ReadOnly(m_bGifStart);
        emit gifstarted(m_bGifStart);
    });
    connect(ui->MoveButton, &QPushButton::clicked, this, [=](){
        m_bGifMove = !m_bGifMove;
        if(m_bGifMove)
        {
            SetMoveState("MoveStart");
        } else {
            SetMoveState("MoveStop");
        }
        emit gifmoveed(m_bGifMove);
    });
    connect(ui->ShowButton, &QPushButton::clicked, this, [=](){
        m_bGifShow = !m_bGifShow;
        if(m_bGifShow)
        {
            SetShowState("ShowStart");
        } else {
            SetShowState("ShowStop");
        }
        emit gifshowed(m_bGifShow);
    });
    connect(ui->LineEditX, &QLineEdit::textChanged, this, [=](QString text){
        Q_UNUSED(text)
        if(!m_bGifselect)
        {
            int x = ui->LineEditX->text().toInt();
            emit gifgeometryed(x, m_pGifWindow.y(),
                               m_pGifWindow.width(), m_pGifWindow.height());
        }
    });
    connect(ui->LineEditY, &QLineEdit::textChanged, this, [=](QString text){
        Q_UNUSED(text)
        if(!m_bGifselect)
        {
            int y = ui->LineEditY->text().toInt();
            emit gifgeometryed(m_pGifWindow.x(), y,
                               m_pGifWindow.width(), m_pGifWindow.height());
        }
    });
    connect(ui->LineEditWidth, &QLineEdit::textChanged, this, [=](QString text){
        Q_UNUSED(text)
        if(!m_bGifselect)
        {
            int w = ui->LineEditWidth->text().toInt();
            emit gifgeometryed(m_pGifWindow.x(), m_pGifWindow.y(),
                               w, m_pGifWindow.height());
        }
    });
    connect(ui->LineEditHeight, &QLineEdit::textChanged, this, [=](QString text){
        Q_UNUSED(text)
        if(!m_bGifselect)
        {
            int h = ui->LineEditHeight->text().toInt();
            emit gifgeometryed(m_pGifWindow.x(), m_pGifWindow.y(),
                               m_pGifWindow.width(), h);
        }
    });
    connect(m_pVidoTimer, &QTimer::timeout, this, [=](){
            QScreen *screen = QApplication::primaryScreen();
            QPixmap pix = screen->grabWindow(0, m_pGifWindow.x(),
                                             m_pGifWindow.y(),
                                             m_pGifWindow.width(),
                                             m_pGifWindow.height());
            QImage image = pix.toImage().convertToFormat(QImage::Format_RGBA8888);
                    //.scaled(m_pGifWindow.width(), m_pGifWindow.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            GifWriteFrame(m_pGifWriter,
                          image.bits(),
                          m_pGifWindow.width(),
                          m_pGifWindow.height(),
                          ui->SpinBoxFps->text().toInt());
            m_iCount++;
            ui->FrameNum->setText(QString("第 %1 帧").arg(m_iCount));
    });

    connect(m_pClose, &QAction::triggered, this, [=](){
        emit closeed();
    });
    /*connect(m_pAbout, &QAction::triggered, this, [=](){
        emit abouted();
    });*/

    SetVideoState("VideoStop");
    SetMoveState("MoveStart");
    SetShowState("ShowStart");
}

void GifButtonWidget::ReadOnly(bool only)
{
    ui->LineEditX->setReadOnly(only);
    ui->LineEditY->setReadOnly(only);
    ui->LineEditWidth->setReadOnly(only);
    ui->LineEditHeight->setReadOnly(only);
    ui->SpinBoxFps->setReadOnly(only);
}

void GifButtonWidget::mousePressEvent(QMouseEvent *event)
{
    QRect imageRect = QRect(ui->Image->x(), ui->Image->y(), ui->Image->width(), ui->Image->height());
    if(event->button() == Qt::LeftButton)
    {
        if(imageRect.contains(event->pos()))
        {
            m_bShowFunction = !m_bShowFunction;
            if(m_bShowFunction)
            {
                QHBoxLayout* BorderLayout = reinterpret_cast<QHBoxLayout*>(ui->BorderWidget->layout());
                BorderLayout->removeWidget(ui->Image);
                BorderLayout->addWidget(ui->FunctionWidget);
                BorderLayout->addWidget(ui->Image);
                BorderLayout->setContentsMargins(5,5,10,5);
                QTimer *timer = new QTimer(this);
                connect(timer, &QTimer::timeout, this, [=](){
                    this->setGeometry(this->x() - 700, this->y(), 760, this->height());
                    ui->FunctionWidget->setVisible(true);
                    timer->stop();
                    timer->deleteLater();
                });
                timer->start(10);
            } else {
                QHBoxLayout* BorderLayout = reinterpret_cast<QHBoxLayout*>(ui->BorderWidget->layout());
                BorderLayout->removeWidget(ui->FunctionWidget);
                BorderLayout->setContentsMargins(5,5,5,5);
                QTimer *timer = new QTimer(this);
                connect(timer, &QTimer::timeout, this, [=](){

                    ui->FunctionWidget->setVisible(false);
                    this->setGeometry(this->x() + 700, this->y(), 60, this->height());
                    timer->stop();
                    timer->deleteLater();
                });
                timer->start(10);
            }
        } else {
            m_bWidgetMove = true;
            m_pPressPos = event->pos();
        }
    } else if(event->button() == Qt::RightButton) {
        if(m_pMenu->isHidden())
        {
            m_pMenu->exec(event->screenPos().toPoint());
        } else {
            m_pMenu->hide();
        }
    }
}

void GifButtonWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bWidgetMove)
    {
        QPoint pos = QPoint(event->pos().x() - m_pPressPos.x(),
                   event->pos().y() - m_pPressPos.y());

        this->move(this->x() + pos.x(), this->y() + pos.y());
        //m_pPressPos = event->pos();
    }
}

void GifButtonWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    m_bWidgetMove = false;
}

void GifButtonWidget::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
}

void GifButtonWidget::On_Gifgeometry(int x, int y, int width, int height)
{
    ui->LineEditX->setText(QString::number(x));
    ui->LineEditY->setText(QString::number(y));
    ui->LineEditWidth->setText(QString::number(width));
    ui->LineEditHeight->setText(QString::number(height));
    m_pGifWindow = QRect(x, y, width, height);
}
