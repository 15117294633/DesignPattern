#include "Route_Oper.h"

Route_Oper::Route_Oper(QWidget *parent)
    : QDialog(parent, Qt::WindowCloseButtonHint | Qt::Drawer)
{
   route=new QComboBox(this);
   tips=new QLabel(this);
   tips->setText(tr("请选择当前路线"));
   m_layout.addWidget(tips);
   m_layout.addWidget(route);
   this->setLayout(&m_layout);
}
 void Route_Oper::Set_Control(IController* con)
 {
    this->Controller=con;
 }
