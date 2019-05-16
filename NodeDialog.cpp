﻿#include "NodeDialog.h"
#include "QDebug"
NodeDialog::NodeDialog(QWidget* parent):
    QDialog(parent, Qt::WindowCloseButtonHint | Qt::Drawer)
  ,Controller(nullptr)
{
     initControl();
     setLayout(&m_layout);
     connectSlot();
}
void NodeDialog::initControl()
{
    this->Node_count_l.setText(tr("节点编号："));
    this->Node_type_l.setText(tr("节点类型："));
    this->Sta_turn_l.setText(tr("站点转向："));
    this->Sta_turn_angle_l.setText(tr("转向角度："));
    this->Node_Desc_l.setText(tr("节点描述："));
    this->Equipment_l.setText(tr("设备使能："));
    this->Equipmenttype_l.setText(tr("设备类型："));

    this->Sta_op_l.setText(tr("站点操作:"));
    this->Sta_op_con_l.setText("操作内容:");
    //节点类型
    Node_type.addItem(tr("站点"));
    Node_type.addItem(tr("分叉点"));
    Node_type.addItem(tr("速度点"));
    //站点操作
    Sta_op.addItem(tr("播放视频"));
    Sta_op.addItem(tr("播放音频"));
    Sta_op.addItem(tr("预留"));
    //站点转向
    Sta_turn.addItem(tr("左转"));
    Sta_turn.addItem(tr("右转"));
    Equipment.addItem(tr("打开"));
    Equipment.addItem(tr("关闭"));

    Equipmenttype.addItem(tr("红外"));
    Equipmenttype.addItem(tr("WIFI"));
    Equipmenttype.addItem(tr("315"));
    Equipmenttype.addItem(tr("433"));

    for(int i=1;i<=999;i++)
    {
        Node_count.addItem(QString::number(i, 10));
    }

    Btn_Cal.setText(tr("取消"));
    Btn_Ok.setText(tr("确认"));
    /*布局*/
    m_layout.setSpacing(10);
    m_layout.addWidget(&Node_count_l, 0, 0);
    m_layout.addWidget(&Node_count, 0, 1);
    m_layout.addWidget(&Node_type_l, 0, 2);
    m_layout.addWidget(&Node_type, 0, 3);

    m_layout.addWidget(&Sta_turn_l, 1, 0);
    m_layout.addWidget(&Sta_turn, 1, 1);
    m_layout.addWidget(&Sta_turn_angle_l,1, 2);
    m_layout.addWidget(&Sta_turn_angle, 1, 3);


    m_layout.addWidget(&Equipment_l, 2, 0);
    m_layout.addWidget(&Equipment, 2, 1);
    m_layout.addWidget(&Equipmenttype_l,2, 2);
    m_layout.addWidget(&Equipmenttype, 2, 3);

    m_layout.addWidget(&Sta_op_l, 3, 0);
    m_layout.addWidget(&Sta_op, 3, 1);
    m_layout.addWidget(&Sta_op_con_l,3, 2);
    m_layout.addWidget(&Sta_op_con, 3, 3);

    m_layout.addWidget(&Node_Desc_l, 4, 0);
   // 用户名输入框 第0行，第1列开始，占1行3列
    m_layout.addWidget(&Node_Desc,4,1,1,3);

    m_layout.addWidget(&Btn_Cal,5,0,1,2);
    m_layout.addWidget(&Btn_Ok,5,2,1,2);
}
void NodeDialog::connectSlot()
{
    connect(&this->Btn_Ok,SIGNAL(clicked(bool)),this,SLOT(Ok_slot()));
    connect(&this->Btn_Cal,SIGNAL(clicked(bool)),this,SLOT(Cal_slot()));
}
void NodeDialog::Ok_slot()
{
    qDebug()<<"Ok_slot()";
    //获取对应节点的属性
    content.node_id=Node_count.currentIndex();
    content.Operator=Sta_op.currentIndex();
    content.type=Node_type.currentIndex();
    content.dir=Sta_turn.currentIndex();
    bool ret;
    content.dir_angle=Sta_turn_angle.text().toInt(&ret,10);
    content.Equ_Sta=Equipment.currentIndex();
    content.Equ_Type=Equipmenttype.currentIndex();
    content.Desc=Node_Desc.text().toLocal8Bit();
    /*传输至控制层*/
    this->Controller->AddNodeData(content);

}
void NodeDialog::Cal_slot()
{
    qDebug()<<"Cal_Slot";
    this->hide();
}
void NodeDialog::Set_Control(IController* con)
{
    this->Controller=con;
}