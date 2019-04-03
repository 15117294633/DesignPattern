#include "Ximage.h"
#include "qdebug.h"
#include "QFileDialog"
#include "XEditView.h"
#include <QMouseEvent>
#include  "XModel.h"
#include "XControllerFactory.h"
#include "IController.h"
Ximage::Ximage(QWidget *parent) : QWidget(parent)
{
    c=IController::Create(new XControllerFactory());
    c->InitDevice(this);
}
void Ximage::open_slot(void)
{
    qDebug() << "XImage::Open()" ;
        //选择图片
    QString filename = QFileDialog::getOpenFileName(this, QStringLiteral("打开图片"), "",
    QStringLiteral("支持的格式(*.png *.jpg *.bmp)"));
    if (filename.isEmpty())
    {
        qDebug() << " Open filename is empty!";
        return;
    }
     c->InitBack(filename.toLocal8Bit());
     update();
}
void Ximage::erase_slot()
{
   c->Set_Current_Index(XERASER);
}
void Ximage::pen_slot()
{
    c->Set_Current_Index(XPEN);
}
 void Ximage::paintEvent(QPaintEvent *e)
 {
     c->Paint();
 }
 void Ximage::mousePressEvent(QMouseEvent *e)
 {
     c->AddModel();
     c->AddData(e->x(),e->y());
 }
 void Ximage::mouseMoveEvent(QMouseEvent*e)
 {
    c->AddData(e->x(),e->y());
     update();
 }
