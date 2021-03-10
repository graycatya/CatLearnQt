#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QFile>
#include <QBuffer>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , image(nullptr)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_OpenFileButton_clicked()
{
    if(image != nullptr)
    {
        delete image;
        image = nullptr;
    }
    auto fileContentReady = [=](const QString &fileName, const QByteArray &fileContent) {
         if (fileName.isEmpty()) {
             // No file was selected
         } else {
             // Use fileName and fileContent
             image = new QImage();
             image->loadFromData(fileContent);
             ui->Image->setPixmap(QPixmap::fromImage(*image));
         }
     };
   QFileDialog::getOpenFileContent("Images (*.png *.jpg)",  fileContentReady);
}

void Widget::on_SaveFileButton_clicked()
{
    if(image != nullptr)
    {
        QByteArray imageData; // obtained from e.g. QImage::save()
        QBuffer buffer(&imageData);
        buffer.open(QIODevice::WriteOnly);
        image->save(&buffer, ui->TypeBox->currentText().toLocal8Bit());
        QString filename = "myimage." + ui->TypeBox->currentText();
        QFileDialog::saveFileContent(imageData, filename);
    }
}
