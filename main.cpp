#include "XimageEdit.h"
#include <QApplication>
#include "Factroy.h"
#include "abstract_factroy.h"
#include"QDebug"
#include "MainWindow.h"
#include "NodeDialog.h"
#include "SqlLite_Helper.h"
#include "IController.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*更换界面*/
//    IController* c=new IController();
//    c->Set_Bit(0);
//    qDebug()<<c->Get_Bit_Unused();
//    qDebug()<<c->Get_Bit_Unused();
//    qDebug()<<c->Get_Bit_Unused();
//    qDebug()<<c->Get_Bit_Unused();
//    qDebug()<<c->Get_Bit_Unused();
//    qDebug()<<c->Get_Bit_Unused();
//    c->clear_bit(2);
//    c->clear_bit(4);
//    qDebug()<<c->Get_Bit_Unused();
//    qDebug()<<c->Get_Bit_Unused();
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

     if(SqlLite_Helper::Get_Obj()->CreateDb())
     {
        qDebug()<<"create database ok";
     }
     else
     {
          qDebug()<<"create database fail";
     }
     Node_Content node;
     SqlLite_Helper::Get_Obj()->FindNodeData(node,1);

     if( SqlLite_Helper::Get_Obj()->Has_Id(1))
     {
        qDebug()<<"ok";
     }
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
