#ifndef XMLHELPER_H
#define XMLHELPER_H
#include "QString"
//方便后期直接导入
#include "map"
class X_Pos;
class XModel;
class Route_node;
class IController;
class XmlHelper
{
private:
    IController* Controller;
protected:
     XmlHelper();
public:
    static XmlHelper* Get_Obj()
    {
        static  XmlHelper obj;
        return &obj;
    }
    void Set_Controller(IController* c);
    void Load_Data_From_Xml();
    void Write_Xml();
    void Add_Xml_Route(int id);
    void AddXml(X_Pos* pos,int id,int type);
    void Read_Xml(int type);
    void RemoveXml(int id,int type);
    void UpdateXml(X_Pos* pos,int id,int type);
};

#endif // XMLHELPER_H
