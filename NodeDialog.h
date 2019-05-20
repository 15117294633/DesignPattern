#ifndef NODEDIALOG_H
#define NODEDIALOG_H
#include "QDialog"
#include "QLabel"
#include <QComboBox>
#include <QLineEdit>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QByteArray>
#include <QPushButton>
#include <IController.h>

class NodeDialog : public QDialog
{
    Q_OBJECT
private:
    Node_Content content;
    IController* Controller;
protected:
    //0,0
    QLabel Node_count_l;
    QComboBox   Node_count;
    //0,1
    QLabel Node_type_l;
    QComboBox   Node_type;

    QLabel Sta_op_l;
    QComboBox   Sta_op;
    //0,1
    QLabel Sta_op_con_l;
    QLabel   Sta_op_con;

    QLabel Sta_turn_l;
    QComboBox  Sta_turn;
    QLabel Sta_turn_angle_l;
    QLineEdit Sta_turn_angle;
    QLabel Node_Desc_l;
    QLineEdit Node_Desc;
    QLabel Equipment_l;
    QComboBox Equipment;
    QLabel Equipmenttype_l;
    QComboBox Equipmenttype;
    QGridLayout m_layout;
    //界面初始化
    QPushButton Btn_Cal;
    QPushButton Btn_Ok;
    void initControl();
    void connectSlot();
public slots:
    void Ok_slot();
    void Cal_slot();
public:
    explicit NodeDialog(QWidget* parent = 0);
    void Set_Control(IController* con);
    void Set_Content();
};

#endif // NODEDIALOG_H
