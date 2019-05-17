#ifndef ROUTE_OPER_H
#define ROUTE_OPER_H
#include <QDialog>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
class IController;
class Route_Oper:public QDialog
{
    Q_OBJECT
private:
    IController* Controller;
    QLabel* tips;
    QPushButton* ok_btn;
    QVBoxLayout m_layout;
public slots:
    void ok_btn_slot();
public:
    QComboBox* route;
    explicit Route_Oper(QWidget* parent = 0);
    void Set_Control(IController* con);
    int get_current_index();
};

#endif // ROUTE_OPER_H
