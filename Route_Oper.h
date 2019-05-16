#ifndef ROUTE_OPER_H
#define ROUTE_OPER_H
#include <QDialog>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
class IController;
class Route_Oper:public QDialog
{
private:
    IController* Controller;
    QComboBox* route;
    QLabel* tips;
    QVBoxLayout m_layout;
public:
    explicit Route_Oper(QWidget* parent = 0);
    void Set_Control(IController* con);
};

#endif // ROUTE_OPER_H
