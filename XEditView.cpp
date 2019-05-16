#include "XEditView.h"
#include "QDebug"
#include "qpainter.h"
#include <QWidget>
/*测试代码*/
#include "XModel.h"
#include "XPenGraph.h"
#include "map"
#include "IGraph.h"
XEditView::XEditView()
{
    out = QImage(1280, 720, QImage::Format_RGB888);
    src = QImage(1280, 720, QImage::Format_RGB888);
}
void XEditView::InitDevice(void *d)
{
   this->device=(QWidget*)d;
   if(this->painter==nullptr)
       painter=new QPainter(&out);
   painter->end();
   painter->begin(&out);

   map<int, IGraph*>::iterator itr = views.begin();
   for (; itr != views.end(); itr++)
   {
        itr->second->Init(painter, &src);
   }
}
//载入背景图
bool XEditView::InitBack(const char *url)
{
     bool ret=true;
     if (!src.load(QString::fromLocal8Bit(url)))
     {
         ret=false;
         qDebug() << " src.load image failed!";

     }
     if (painter->isActive())
         painter->end();
     out = src.copy();
    painter->begin(&out);
     return ret;
}
void XEditView::Update(XSubject *sub)
{

   if (!sub)return;
       //XModel
    XModel *m = static_cast<XModel*>(sub);
    //实际拿到是对应的
    views[m->type]->Draw(m);
}
//绘制结果
void XEditView::Paint()
{
    //在device窗口绘制
    QPainter p(device);

    p.drawImage(0, 0, out);
}
XEditView::~XEditView()
{

}
