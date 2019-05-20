#ifndef ILOCSQL_H
#define ILOCSQL_H
class Node_Content;
class My_Sql
{
public:
    virtual bool CreateDb()=0;
    virtual bool Has_Id(int id)=0;
    virtual void InsertIntoData(Node_Content* node)=0;
    virtual void DeleteNode(int id)=0;
    virtual void ModifiNode(Node_Content* node)=0;
    virtual void FindNodeData(Node_Content& node,int id)=0;
};
#endif // ILOCSQL_H
