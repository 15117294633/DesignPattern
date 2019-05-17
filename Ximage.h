#ifndef XIMAGE_H
#define XIMAGE_H

#include <QWidget>
#include <QImage>
#include <QMenu>
#include <QSharedPointer>
#include <NodeDialog.h>
class IController;
class MainWindow;
class RouteMange;
class Ximage : public QWidget
{
    Q_OBJECT

private:
    MainWindow* main_window;
    QSharedPointer<NodeDialog> current_node_Dlg;
    QSharedPointer<RouteMange> route_mange;
public:
    //查找对应的ACTION
    QAction* findToolBarAction(QString text);
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent*e);
    void mouseDoubleClickEvent(QMouseEvent *event);
    explicit Ximage(QWidget *parent = nullptr);
protected:
    IController *c = 0;
    QMenu* pMenu;
public slots:
    void Open_slot_t();
    void erase_slot();
    void pen_slot();
    void rect_slot();
    void circle_slot();
    void node_selected();
    void do_move_slot();
    void on_action_trigered();
    void on_delete_action_trigered();
    void add_node_slot();
    void remove_node_slot();
    void route_mange_slot();
    void import_slot();

};

#endif // XIMAGE_H
