#include "RouteMange.h"
#include "QDebug"
#include "IController.h"
RouteMange::RouteMange(QWidget *parent) : QDialog(parent),
    route_oper(new Route_Oper(this))
{
    setWindowTitle("route mange");
    changeroute=new QPushButton(this);
    changeroute->setText(tr("更改线路"));
    deleteroute=new QPushButton(this);
    deleteroute->setText(tr("删除线路"));
    showroute=new QPushButton(this);
    showroute->setText(tr("显示线路"));
    addroute=new QPushButton(this);
    addroute->setText(tr("添加线路"));
    m_layout.addWidget(changeroute);
    m_layout.addWidget(deleteroute);
    m_layout.addWidget(showroute);
    m_layout.addWidget(addroute);
    this->setLayout(&m_layout);
    connect(changeroute,SIGNAL(clicked(bool)),this,SLOT(route_change_slot()));
    connect(deleteroute,SIGNAL(clicked(bool)),this,SLOT(route_delete_slot()));
    connect(addroute,SIGNAL(clicked(bool)),this,SLOT(route_add_slot()));
    connect(showroute,SIGNAL(clicked(bool)),this,SLOT(route_show_slot()));

}
 void RouteMange::Set_Control(IController* con)
 {
     this->Controller=con;
     route_oper->Set_Control(con);
//     this->close();
 }

 void RouteMange::route_change_slot()
 {
    route_oper->show();
    if(this->Controller!=nullptr)
    {
        this->Controller->Set_Current_Index(XCHANGEROUTE);
    }
    qDebug()<<"change route";
    this->close();
    Add_Items();
 }
 void RouteMange::route_delete_slot()
 {
     route_oper->show();
     if(this->Controller!=nullptr)
     {
         this->Controller->Set_Current_Index(XDELETROUTE);
     }
     qDebug()<<"delete route";
     Add_Items();
     this->close();
 }
 void RouteMange::route_add_slot()
 {
     route_oper->show();
     if(this->Controller!=nullptr)
     {
         this->Controller->Set_Current_Index(XADDROUTE);
         /*加入对应的节点*/
         Controller->Add_Route();
     }
     Add_Items();
     this->close();
 }
 void RouteMange::route_show_slot()
 {
     route_oper->show();
     if(this->Controller!=nullptr)
     {
         this->Controller->Set_Current_Index(XSHOWROUTE);
     }
     Add_Items();
     qDebug()<<"show route";
     this->close();
 }
 void RouteMange::Add_Items()
 {
     int len;
     this->route_oper->route->clear();
     len=this->Controller->Get_route_count();
     if(len>=1)
      {
            std::map<int,std::vector<Route_node>*>::iterator iter;
            for(iter=this->Controller->route_map.begin();iter!=this->Controller->route_map.end();iter++)
            {
                QString str=QString("route%1").arg(iter->first);
                this->route_oper->route->addItem(str);
            }
      }

 }
