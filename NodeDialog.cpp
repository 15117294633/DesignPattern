#include "NodeDialog.h"
#include "QDebug"
#include  "XModel.h"
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

    Sta_op.addItem(tr("播放视频"));
    Sta_op.addItem(tr("播放音频"));
    Sta_op.addItem(tr("预留"));

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
    content.node_id=Node_count.currentIndex()+1;
    content.Operator=Sta_op.currentIndex()+1;
    content.type=Node_type.currentIndex()+1;
    content.dir=Sta_turn.currentIndex()+1;
    bool ret;
    content.dir_angle=Sta_turn_angle.text().toInt(&ret,10);
    content.Equ_Sta=Equipment.currentIndex()+1;
    content.Equ_Type=Equipmenttype.currentIndex()+1;
    content.Desc=Node_Desc.text();
    /*传输至控制层*/
    this->Controller->AddNodeData(content);   
    this->close();
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
void NodeDialog::Set_Content()
{
    this->Node_count.setCurrentIndex(Controller->m->id-1);
    if(Controller->Get_Sql()->Has_Id(Controller->m->id))
    {
         //初始化Data
        Controller->Get_Sql()->FindNodeData(content,Controller->m->id);
        //初始化对应的gui
        this->Node_type.setCurrentIndex(content.type-1);
        this->Sta_turn.setCurrentIndex(content.dir-1);
        this->Equipment.setCurrentIndex(content.Equ_Sta-1);
        this->Equipmenttype.setCurrentIndex(content.Equ_Type-1);
        //站点操作内容
        this->Sta_op.setCurrentIndex(content.Operator-1);
        this->Sta_turn_angle.setText(QString::number(content.dir_angle));
        this->Node_Desc.setText(content.Desc);

    }
    else
    {
        this->Node_Desc.setText("");
        this->Node_type.setCurrentIndex(0);
        this->Sta_turn.setCurrentIndex(0);
        this->Equipment.setCurrentIndex(0);
        this->Equipmenttype.setCurrentIndex(0);
        this->Sta_op.setCurrentIndex(0);
        this->Sta_turn_angle.setText(QString::number(90));
        this->Node_Desc.setText(content.Desc);
        content.Init();
    }
}
