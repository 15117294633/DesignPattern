#include "XEditView.h"
#include "QDebug"
#include "qpainter.h"
#include <QWidget>
/*测试代码*/
#include "XModel.h"
#include "XPenGraph.h"
#include "map"
#include "IGraph.h"
//XPenGraph xpen;
XEditView::XEditView()
{
    out = QImage(1280, 720, QImage::Format_RGB888);
    src = QImage(1280, 720, QImage::Format_RGB888);
}
void XEditView::InitDevice(void *d)
{
   this->device=(QWidget*)d;
   if(this->painter==nullptr)
       painter=new QPainter();
   painter->end();
   painter->begin(&out);

   map<int, IGraph*>::iterator itr = views.begin();
   for (; itr != views.end(); itr++)
   {
           itr->second->Init(painter, &src);;
   }
   //xpen.Init(painter,&src);
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
    views[m->type]->Draw(m);
//    map<int, IGraph*>::iterator itr = views.begin();
//    for (; itr != views.end(); itr++)
//    {
//        itr->second->Draw(m);
//    }
   // xpen.Draw(m);

//    int size = m->pos.size();

//    QPainter p(&out);
//    for (int i = 1; i < size; i++)
//    {
//       p.drawLine(QLine(m->pos[i - 1].x, m->pos[i - 1].y, m->pos[i].x, m->pos[i].y));
//    }
}
//绘制结果
void XEditView::Paint()
{
    //QPainter p(device);
    // p.drawImage(0, 0, src);
    //在device窗口绘制
    QPainter p(device);

    p.drawImage(0, 0, out);
    //绘制图片
//    p.drawImage(0, 0, src);
//    //所有坐标的数量
//    int size = pos.size();
//    //从1开始，划线要两个点
//    for (int i = 1; i < size; i++)
//    {
//        //绘制线，开始点到结束点
//        p.drawLine(QLine(pos[i - 1].x, pos[i - 1].y, pos[i].x, pos[i].y));
//    }
}
XEditView::~XEditView()
{

}
