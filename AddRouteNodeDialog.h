#ifndef ADDROUTENODEDIALOG_H
#define ADDROUTENODEDIALOG_H
#include "QDialog"
#include "QLabel"
#include "qcombobox.h"
#include "QVBoxLayout"
#include "QPushButton"
class IController;
class AddRouteNode:public QDialog
{

    Q_OBJECT
private:
    IController* Controller;
    QLabel* desc;
    QComboBox* route_node_count;
    QVBoxLayout m_layout;
    QPushButton* ok_btn;
public slots:
    void ok_btn_slot();
public:
    explicit AddRouteNode(QWidget *parent = 0);
    void Set_Control(IController* con);
    void Set_Curent_index(int index);
};

#endif // ADDROUTENODEDIALOG_H
