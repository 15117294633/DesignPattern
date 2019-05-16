#include "XimageEdit.h"
#include <QApplication>
#include "Factroy.h"
#include "abstract_factroy.h"
#include"QDebug"
#include "MainWindow.h"
#include "NodeDialog.h"

#include "IController.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*更换界面*/
//    IController* c=new IController();
//    c->Add_Route(0);
//    for(int i=0;i<10;i++)
//    {
//        Route_node node;
//        node.id=10-i;
//        c->curren_route->push_back(node);
//    }


//     c->Sort_Route_node();
//     for(int i=0;i<10;i++)
//     {
//         qDebug()<<c->curren_route->at(i).id;
//     }

//    qDebug()<<c->Find_Route_node(5);


     MainWindow w;
     w.show();


    //NodeDialog dia;

    //dia.show();
/*
    XimageEdit w;
    w.show();
*/
    return a.exec();
}
