#include "SqlLite_Helper.h"
#include "IController.h"

bool SqlLite_Helper::CreateDb()
{

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db");
    db.setUserName("root");
    db.setPassword("123456");
    if(!db.open()) return false;

     query=new QSqlQuery(db);
     query->exec("create table Node(id int primary key,type int,operator int,turn int,angle varchar,control int,control_type int,desc varchar)");
     query->exec("create table Node_Loc(id int primary key,x_pos int,y_pos int)");
     //线路的总数写入至配置文件当中
     db.close();
     return true;
}
//插入操作
void SqlLite_Helper::InsertIntoData(Node_Content* node)
{
    db.open();
    sql=QString("insert into Node values(%1,%2,%3,%4,%5,%6,%7,'%8')")
            .arg(node->node_id).arg(node->type).arg(node->Operator)
            .arg(node->dir).arg(node->dir_angle).arg(node->Equ_Sta)
            .arg(node->Equ_Type).arg(node->Desc);
    query->exec(sql);
    qDebug()<<sql;
    db.close();

}
void SqlLite_Helper::DeleteNode(int id)
{
  db.open();
  sql=QString("delete from Node where id = %1").arg(id);
  query->exec(sql);
}
void SqlLite_Helper::ModifiNode(Node_Content* node)
{
   //修改一个数据
   db.open();
   sql=QString("update Node set type=%2,operator=%3,turn=%4,angle=%5,control=%6,control_type=%7,desc='%8'where id=%1")
            .arg(node->node_id).arg(node->type).arg(node->Operator).arg(node->dir)
            .arg(node->dir_angle).arg(node->Equ_Sta) .arg(node->Equ_Type)
            .arg(QString(node->Desc));
   query->exec(sql);
   qDebug()<<sql;
   db.close();
}
//节点号 类型 操作 站点转向 转向的角度 场馆控制 设备类型 节点的描述信息
void SqlLite_Helper::FindNodeData(Node_Content& node,int id)
{
   db.open();
   sql = QString("select * from Node where id = '%1'").arg(id);
   query->exec(sql);
   qDebug()<<sql;
   while( query->next())
   {
      node.type=query->value(1).toInt();
      node.Operator=query->value(2).toInt();
      node.dir=query->value(3).toInt();
      node.dir_angle=query->value(4).toInt();
      node.Equ_Sta=query->value(5).toInt();
      node.Equ_Type=query->value(6).toInt();
      node.Desc=query->value(7).toString();
      qDebug()<<query->value(7).toString();
   }
   db.close();
}
bool SqlLite_Helper::Has_Id(int id)
{
    bool ret=false;
    db.open();
    sql = QString("select * from Node where id = '%1'").arg(id);
    qDebug()<<sql;
    query->exec(sql);
    while( query->next())
    {
        ret=true;
    }

    db.close();
    return ret;
}
SqlLite_Helper::SqlLite_Helper()
{

}
