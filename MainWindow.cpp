#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMenu>
#include <QIcon>
#include <QSize>
#include <QStatusBar>
#include "Ximage.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*构造工具栏*/
    initToolBar();
    connect(ui->openfile,SIGNAL(clicked(bool)),ui->image,SLOT(Open_slot_t()));
    connect(ui->route,SIGNAL(clicked(bool)),ui->image,SLOT(route_mange_slot()));
    connect(ui->data_import,SIGNAL(clicked(bool)),ui->image,SLOT(import_slot()));
}

bool MainWindow::initToolBar()
{
    bool ret = true;
    QToolBar* tb = addToolBar("Tool Bar");
    ToolBar=tb;
    tb->setIconSize(QSize(16, 16));

    ret = ret && initEditToolItem(tb);

    return ret;
}
bool MainWindow::initEditToolItem(QToolBar* tb)
{
    bool ret = true;
    QAction* action = NULL;

    ret = ret && makeAction(action, tb, "Arrow", ":/pic/sel.png");

    if( ret )
    {
        connect(action, SIGNAL(triggered()), ui->image, SLOT(do_move_slot(void)));
        action->setEnabled(true);
        tb->addAction(action);
    }

    ret = ret && makeAction(action, tb, "Node", ":/pic/node.png");

    if( ret )
    {
        connect(action, SIGNAL(triggered()), ui->image, SLOT(node_selected()));
        action->setEnabled(true);
        tb->addAction(action);
    }

    ret = ret && makeAction(action, tb, "Add Route", ":/pic/add.png");

    if( ret )
    {
        connect(action, SIGNAL(triggered()), ui->image, SLOT(add_node_slot()));
        action->setEnabled(true);
        tb->addAction(action);
    }

    ret = ret && makeAction(action, tb, "Remove node", ":/pic/remove.png");

    if( ret )
    {
        connect(action, SIGNAL(triggered()), ui->image, SLOT(remove_node_slot()));
        action->setEnabled(true);
        tb->addAction(action);
    }

    return ret;
}
bool MainWindow::makeAction(QAction*& action, QWidget* parent, QString text, int key)
{
    bool ret = true;

    action = new QAction(text, parent);

    if( action != NULL )
    {
        action->setShortcut(QKeySequence(key));
    }
    else
    {
        ret = false;
    }

    return ret;
}
bool MainWindow::makeAction(QAction*& action, QWidget* parent, QString tip, QString icon)
{
    bool ret = true;

    action = new QAction("", parent);

    if( action != NULL )
    {
        action->setToolTip(tip);
        action->setIcon(QIcon(icon));
    }
    else
    {
        ret = false;
    }

    return ret;
}


MainWindow::~MainWindow()
{
    delete ui;
}
