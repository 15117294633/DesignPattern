#ifndef ICONTROLLER_H
#define ICONTROLLER_H
class XModel;
class IView;
class Ioperator;
#include "MySql.h"
#include "IControllerFactroy.h"
#include "vector"
#include "QPointer"
#include "QDebug"
#include "build.h"
#include "map"
enum XSTATUS
{
    XPEN,
    XERASER,
    XRECT,
    XIMAGE,
    XCIRCLE,
    XMOVE,
    XADDROUTE,
    XDELETROUTE,
    XCHANGEROUTE,
    XSHOWROUTE,
};
struct Node_Content
{
    int node_id;
    int type;
    int Operator;
    int content;
    int dir;
    int dir_angle;
    int Equ_Sta;
    int Equ_Type;
    QString Desc;
    Node_Content& operator = (const Node_Content& obj)
    {
       if(this!=&obj)
       {
           this->node_id=obj.node_id;
           type= obj.type;
           Operator= obj.Operator;
           content= obj.content;
           dir= obj.dir;
           dir_angle= obj.dir_angle;
           Equ_Sta= obj.Equ_Sta;
           Equ_Type= obj.Equ_Type;
           Desc= obj.Desc;
           qDebug()<<Desc;
       }
       return *this;
    }
    void Init()
    {
        type=1;
        Operator=1;
        dir=3;
        dir_angle=60;
        Equ_Sta=1;
        Equ_Type=0;
        Desc="";
    }
};
struct Route_node
{
   int id; //当前节点路径id
   bool operator < (const Route_node &m) {
                return id < m.id;
          }
   bool operator = (const Route_node &m) {
        return id =m.id;
   }
};
class IController
{
public:
    IController();
    ~IController();
    //生成对应的对象工厂
    static IController* Create(IControllerFactroy *f);
    /*添加了一个门面*/
    virtual void InitDevice(void *d);
    virtual bool InitBack(const char *url);
    virtual void Paint();
    /*模型对应的操作*/
    virtual void AddModel(int s=-1);
    virtual void RemoveModel();
    virtual void do_contral(int x,int y);
    virtual bool Is_Valid_Point(int x,int y);
    //模型添加节点数据
    virtual void AddNodeData(Node_Content& node);
    //更新数据
    virtual void AddData(int x,int y);

    virtual void Set_Current_Index(XSTATUS sta);
    virtual XSTATUS Get_Current_Data();

    /*通知视图控件进行update*/
    virtual void NotfyAll();
    //将当前的模型赋值为NULL
    virtual void SetModel();
    //添加路线
    virtual int Get_route_count();
    virtual void Add_Route();
    virtual void Add_Route(int num);
    virtual void Delete_Route(int num);
    virtual void Get_route(int num);
    virtual void Edit_route(int num);

    virtual void Sort_Route_node();
    virtual int Find_Route_node(int index);
    virtual void Remove_Route_node();
    virtual void Add_Route_ndoe();
    virtual void Show_ALL_Node();
    /*获取位图*/
    virtual int Get_Bit_Unused();
    virtual void Set_Bit(int value);
    virtual void clear_bit(int n);
    /*update*/
    virtual void update_c();
    //路径导出功能
    virtual void import_route(QString fileName);
    std::vector<Route_node>* curren_route;
    XModel *m;
    /*队列的方式存储对应的线路_map结构存储对应的数据*/
    std::map<int,std::vector<Route_node>*> route_map;
    My_Sql* Get_Sql();
    //加载数据
    void Load_Data_From_Xml();
    void Load_Data_From_Sql();
    IView *v;
    IControllerFactroy* factroy;
    std::vector<XModel*> m_task;
protected:
    int m_current_route;
    /*位图实现对应的路线*/
    int m_route_used;
    My_Sql* sql;
    Builder* Export;
    Ioperator* oper_do;
    //所有的节点表
    XSTATUS current_index = XPEN;

};

#endif // ICONTROLLER_H
