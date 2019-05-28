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
#include "XmlHelper.h"
#include "AddRouteNodeDialog.h"
Ximage::Ximage(QWidget *parent)
    : QWidget(parent),
      current_node_Dlg(new NodeDialog(this)),
      addRouteNodeDialog(new AddRouteNode(this)),
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

    /*路线管理弹出式菜单*/
    pMenu_r=new QMenu(this);

    QAction *pAction3 = new QAction(pMenu_r);
    pAction3->setText(tr("删除路线节点"));
    pMenu_r->addAction(pAction3);
    connect(pAction3,SIGNAL(triggered()),this,SLOT(remove_route_node()));

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

}
void Ximage::import_slot()
{
  QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                                        "/home",
                                                                        QFileDialog::ShowDirsOnly
                                                                        | QFileDialog::DontResolveSymlinks);
  this->c->import_route(dir);
  c->import_route("route");
}
void Ximage::remove_node_slot()
{
    findToolBarAction("Arrow")->setEnabled(true);
    findToolBarAction("Node")->setEnabled(true);
     c->Load_Route_Node();
//    this->c->RemoveModel();
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
/*路线节点管理*/
void Ximage::add_route_node()
{

}
void Ximage::remove_route_node()
{
    c->RemoveModel();
}
//节点管理
void Ximage::on_action_trigered()
{
    //调用对应的策略更新组件
    addRouteNodeDialog->show();
    addRouteNodeDialog->Set_Control(c);
    int ret=c->Find_Route_node_before();
    qDebug()<<"Find route before"<<ret;
    addRouteNodeDialog->Set_Curent_index(ret);
}
void Ximage::on_delete_action_trigered()
{
    c->Remove_Route_node();
    update();
}

 void Ximage::mousePressEvent(QMouseEvent *e)
 {
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
               pMenu->popup(e->globalPos());
           }

      }
      if(e->button() ==Qt::RightButton&&(c->Get_Current_Data()==XMOVE))
      {
          if(c->Is_Valid_Point(e->x(),e->y()))
          {
              pMenu_r->popup(e->globalPos());
          }
      }

 }
 void Ximage::mouseReleaseEvent(QMouseEvent *e)
 {
     qDebug()<<"mouseReleaseEvent";
     if((c->Get_Current_Data()==XMOVE)||(c->Get_Current_Data()==XCIRCLE))
     {
         if(c->m!=nullptr)
         {
            qDebug()<<c->m->id;
            qDebug()<<e->x()<<e->y();
            X_Pos pos(e->x(),e->y());
            XmlHelper::Get_Obj()->UpdateXml(&pos,c->m->id,0);
         }
     }
     qDebug()<<"mouseReleaseEvent end";
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
