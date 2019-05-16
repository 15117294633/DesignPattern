#ifndef ROUTEMANGE_H
#define ROUTEMANGE_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSharedPointer>
#include "Route_Oper.h"
class   IController;
class RouteMange : public QDialog
{
    Q_OBJECT
private:
      QSharedPointer<Route_Oper> route_oper;
    IController* Controller;
    QPushButton* changeroute;
    QPushButton* deleteroute;
    QPushButton* showroute;
    QPushButton* addroute;
    QVBoxLayout m_layout;
public:
    explicit RouteMange(QWidget *parent = nullptr);
    void Set_Control(IController* con);
public slots:
    void route_change_slot();
    void route_delete_slot();
    void route_add_slot();
    void route_show_slot();
};

#endif // ROUTEMANGE_H
