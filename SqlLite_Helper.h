#ifndef SQLLITE_HELPER_H
#define SQLLITE_HELPER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <MySql.h>
class Node_Content;
class SqlLite_Helper:public My_Sql
{
public:
    static SqlLite_Helper* Get_Obj()
    {
        static  SqlLite_Helper obj;
        return &obj;
    }
    /*节点表中*/
    bool CreateDb();
    bool Has_Id(int id);
    void InsertIntoData(Node_Content* node);
    void DeleteNode(int id);
    void ModifiNode(Node_Content* node);
    void FindNodeData(Node_Content& node,int id);
    /*XML的方*/
private:
   QSqlDatabase db;
   QSqlQuery* query;
   QString sql;
   SqlLite_Helper();
};

#endif // SQLLITE_HELPER_H
