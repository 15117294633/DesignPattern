#include "AddRouteNodeDialog.h"
#include "IController.h"
AddRouteNode::AddRouteNode(QWidget *parent):
    QDialog(parent)
{
    route_node_count=new QComboBox(this);
     route_node_count->addItem("root");
    for(int i=0;i<256;i++)
    {
        QString str=QString::number(i+1);
        route_node_count->addItem(str);
    }
    desc=new QLabel(this);
    desc->setText(tr("请选择前向节点"));
    ok_btn=new QPushButton(this);
    ok_btn->setText(tr("确认添加"));

    m_layout.addWidget(desc);
    m_layout.addWidget(route_node_count);
    m_layout.addWidget(ok_btn);
    this->setLayout(&m_layout);
    connect(this->ok_btn,SIGNAL(clicked(bool)),this,SLOT(ok_btn_slot()));
}
void AddRouteNode::Set_Control(IController* con)
{
    this->Controller=con;
}
void AddRouteNode::Set_Curent_index(int index)
{
    this->route_node_count->setCurrentIndex(index);
}
void AddRouteNode::ok_btn_slot()
{
    int index=route_node_count->currentIndex();
    this->Controller->Add_Route_node(index);
    this->close();
}
