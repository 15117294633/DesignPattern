#include "XimageEdit.h"
#include <QApplication>
#include "Factroy.h"
#include "abstract_factroy.h"
#include"QDebug"
#include "MainWindow.h"
#include "NodeDialog.h"
#include "SqlLite_Helper.h"
#include "IController.h"
#include "XModel.h"
#include "iniFilePath.h"
#include "Route_Id_Man.h"
#include "Init_Param.h"
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
//      X_Pos pos(999,1050);
//     XmlHelper::Get_Obj()->Write_Xml();
//     XmlHelper::Get_Obj()->Add_Xml_Route(1);
//     XmlHelper::Get_Obj()->Add_Xml_Route(2);
//     XmlHelper::Get_Obj()->Add_Xml_Route(3);

//    XmlHelper::Get_Obj()->AddXml(&pos,1,0);
//    XmlHelper::Get_Obj()->AddXml(&pos,2,0);
//    XmlHelper::Get_Obj()->AddXml(&pos,3,0);

//    XmlHelper::Get_Obj()->AddXml(&pos,4,1);
//    XmlHelper::Get_Obj()->AddXml(&pos,5,1);
//    XmlHelper::Get_Obj()->AddXml(&pos,6,1);
//    XmlHelper::Get_Obj()->RemoveXml(2,0);
//    XmlHelper::Get_Obj()->AddXml(&pos,4);
//    X_Pos pos1(100,100);
//    XmlHelper::Get_Obj()->UpdateXml(&pos1,3,0);
//    XmlHelper::Get_Obj()->Read_Xml(pos1,0);
    Init_Param::Get_Obj()->Creat_Folder();
    MainWindow w;
    w.show();
//      Route_Id_Man::Get_Obj()->Set_Route_Bit(0XFFFFFFFF,0);
//      Route_Id_Man::Get_Obj()->Set_Route_Bit(0XFFFFFFFF,1);

//      Route_Id_Man::Get_Obj()->Set_Route_Bit(0XFFFFFFFF,2);
//      Route_Id_Man::Get_Obj()->Set_Route_Bit(0XFFFFFFFF,3);
//      Route_Id_Man::Get_Obj()->Set_Route_Bit(0XFFFFFFFF,4);

//      Route_Id_Man::Get_Obj()->Set_Route_Bit(0XFFFFFFFF,5);

//      for(int i=0;i<36;i++)
//      {
//          qDebug()<<Route_Id_Man::Get_Obj()->Get_Route_Id();
//      }
//     Route_Id_Man::Get_Obj()->Clear_Route_Id(1);
    //NodeDialog dia;

    //dia.show();
/*
    XimageEdit w;
    w.show();
*/
    return a.exec();
}
