#include "Route_Oper.h"
#include "IController.h"
Route_Oper::Route_Oper(QWidget *parent)
    : QDialog(parent, Qt::WindowCloseButtonHint | Qt::Drawer)
{
   route=new QComboBox(this);
   tips=new QLabel(this);
   tips->setText(tr("请选择当前路线"));
   ok_btn=new QPushButton(this);
   ok_btn->setText(tr("确认"));
   m_layout.addWidget(tips);
   m_layout.addWidget(route);
   m_layout.addWidget(ok_btn);
   this->setLayout(&m_layout);
   /*连接信号与槽*/
   connect(this->ok_btn,SIGNAL(clicked(bool)),this,SLOT(ok_btn_slot()));

}
void Route_Oper::ok_btn_slot()
{
    int type=this->Controller->Get_Current_Data();
    int index=get_current_index();
    switch (type) {
    case XDELETROUTE:
       this->Controller->Delete_Route(index);
        break;
    case XSHOWROUTE:
        this->Controller->Get_route(index);
        break;
    case XCHANGEROUTE:
        this->Controller->Edit_route(index);
        break;
    }
    this->Controller->update_c();
    this->close();
}
void Route_Oper::Set_Control(IController* con)
{
    this->Controller=con;
}
int Route_Oper::get_current_index()
{
    int index=this->route->currentIndex();
    QString str=this->route->itemText(index);
    bool ret;
    int loc=str.right(1).toInt(&ret);
    return loc;
}

