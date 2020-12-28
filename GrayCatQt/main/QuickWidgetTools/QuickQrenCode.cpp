#include "QuickQrenCode.h"
#include "ui_QuickQrenCode.h"
#include "CatWidget/QrenCode/Src/QrenCodeQml/QuickQrenCodeParentItem.h"

#include <CatLog>

QuickQrenCode::QuickQrenCode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuickQrenCode)
{
    ui->setupUi(this);
    InitProperty();
    InitConnect();
}

QuickQrenCode::~QuickQrenCode()
{
    QString log = QString("QuickQrenCode Delete...");
    CATLOG::CatLog::__Write_Log(DEBUG_LOG_T(log.toStdString()));
    delete ui;
}

void QuickQrenCode::InitProperty()
{
    qmlRegisterType<QuickQrenCodeParentItem>("QParentQrenCode", 1, 0, "ParentQrenCode");
    QUrl source("qrc:/qml/CatQrenCode.qml");
    //this->setWindowFlag(Qt::FramelessWindowHint);
    //setAttribute(Qt::WA_TranslucentBackground, true);
    // 如果此属性设置为SizeRootObjectToView，视图将自动将根项调整为视图的大小。
    //ui->QuickQrenCodeWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    ui->QuickQrenCodeWidget->setSource(source);
    ui->QuickQrenCodeWidget->setClearColor(QColor(Qt::transparent));

}

void QuickQrenCode::InitConnect()
{
    QQuickItem *item = ui->QuickQrenCodeWidget->rootObject();
    connect(ui->QrenCodeEdit, SIGNAL(textEdited(QString)), item, SIGNAL(setTextCode(QString)));
    ui->QrenCodeEdit->setText("www.graycatya.com");
}

