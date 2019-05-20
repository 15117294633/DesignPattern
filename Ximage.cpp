#include "Ximage.h"
#include "XEditView.h"
#include <QMouseEvent>
#include  "XModel.h"
#include "XControllerFactory.h"
#include "IController.h"
#include "QDebug"
#include "QFileDialog"
#include "QCursor"
#include "QMessageBox"
#include "MainWindow.h"
#include "RouteMange.h"
Ximage::Ximage(QWidget *parent)
    : QWidget(parent),
      current_node_Dlg(new NodeDialog(this)),
      route_mange(new RouteMange(this))
{
    /*创建一个菜单项*/
    main_window=(MainWindow*)parent;
        qDebug()<<main_window;
     /*用函数初始化*/
    pMenu=new QMenu(this);
    QAction *pAction = new QAction(pMenu);
    pAction->setText(tr("添加节点"));
    pMenu->addAction(pAction);
    connect(pAction,SIGNAL(triggered()),this,SLOT(on_action_trigered()));

    QAction *pAction1 = new QAction(pMenu);
    pAction1->setText(tr("删除节点"));
    connect(pAction1,SIGNAL(triggered()),this,SLOT(on_delete_action_trigered()));
    pMenu->addAction(pAction1);

    c=IController::Create(new XControllerFactory());
    c->InitDevice(this);
    current_node_Dlg->Set_Control(c);
    route_mange->Set_Control(c);
}
void Ximage::Open_slot_t(void)
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
//画图
void Ximage::circle_slot()
{
  c->Set_Current_Index(XCIRCLE);
}
void Ximage::rect_slot()
{
    c->Set_Current_Index(XRECT);
}
void Ximage::add_node_slot()
{
//     int count=c->Get_route_count();
//     QString str=QString("add route is %1").arg(count);
//     int ret=QMessageBox::information(this,"information",str,QMessageBox::Ok | QMessageBox::Cancel,QMessageBox::Cancel);
//     if(ret==QMessageBox::Ok)
//     {
//        //添加一个对应的路线
//         c->Add_Route(count+1);
//        qDebug()<<"ADD OK";
//     }
}
void Ximage::import_slot()
{
  QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                                        "/home",
                                                                        QFileDialog::ShowDirsOnly
                                                                        | QFileDialog::DontResolveSymlinks);
  this->c->import_route(dir);
}
void Ximage::remove_node_slot()
{
    findToolBarAction("Arrow")->setEnabled(true);
    findToolBarAction("Node")->setEnabled(true);
   this->c->RemoveModel();
}
void Ximage::paintEvent(QPaintEvent *e)
{
    c->Paint();
}
void Ximage::node_selected()
{
    findToolBarAction("Arrow")->setEnabled(true);
    findToolBarAction("Node")->setEnabled(false);
    c->Set_Current_Index(XCIRCLE);
    c->Show_ALL_Node();
    update();
}
void  Ximage::do_move_slot(void)
{
    /*将当前模型赋值为kong*/
    findToolBarAction("Arrow")->setEnabled(false);
    findToolBarAction("Node")->setEnabled(true);

    c->SetModel();
    c->Set_Current_Index(XMOVE);
}
void Ximage::route_mange_slot()
{
    findToolBarAction("Arrow")->setEnabled(true);
    findToolBarAction("Node")->setEnabled(false);
    route_mange->show();
}
void Ximage::on_action_trigered()
{
    //调用对应的策略更新组件
    c->Add_Route_ndoe();
    update();
}
void Ximage::on_delete_action_trigered()
{
    c->Remove_Route_node();
    update();
}

 void Ximage::mousePressEvent(QMouseEvent *e)
 {
     qDebug()<<e->x()<<e->y();
     /*模型用于添加数据*/
     if(e->button()==Qt::LeftButton)
     {
         if(c->Get_Current_Data()==XCIRCLE)
         {
             c->AddModel();
         }
         else if(c->Get_Current_Data()==XMOVE)
         {
             c->SetModel();
         }
         qDebug()<<"Mouse press";
         c->do_contral(e->x(),e->y());
        update();
     }
      //判断事件为鼠标右键   右键弹出菜单
      if (e->button() == Qt::RightButton&&(c->Get_Current_Data()==XADDROUTE||
                                        c->Get_Current_Data()==XCHANGEROUTE))
      {
           c->SetModel();
           if(c->Is_Valid_Point(e->x(),e->y()))
           {
//               c->do_contral(e->x(),e->y());
               pMenu->popup(e->globalPos());
           }

      }

 }
 void Ximage::mouseMoveEvent(QMouseEvent*e)
 {

    if(e->buttons()==Qt::LeftButton)
    {
        qDebug()<<"Mouse Move";
        c->do_contral(e->x(),e->y());
        update();
    }

 }
 void Ximage::mouseDoubleClickEvent(QMouseEvent *event)
 {
     //只有被选择状态下才能编辑
     if( findToolBarAction("Node")->isEnabled())
     {
         if(c->Is_Valid_Point(event->x(),event->y()))
         {
            current_node_Dlg->Set_Content();
            current_node_Dlg->show();

         }
     }
 }
QAction* Ximage::findToolBarAction(QString text)
{
    QAction* ret = NULL;

    const QObjectList& list = main_window->ToolBar->children();

    for(int i=0; i<list.length(); i++)
    {
        QAction* retf=qobject_cast<QAction*>(list[i]);
        if(retf!=nullptr)
        {
            if(retf ->toolTip().startsWith(text))
            {
                ret=retf;
                break;
            }
        }
    }
    return ret;
}
