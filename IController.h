#ifndef ICONTROLLER_H
#define ICONTROLLER_H
class XModel;
class IView;
class Ioperator;
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
    QByteArray Desc;
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
    virtual void do_contral(int x,int y);
    virtual bool Is_Valid_Point(int x,int y);
    //模型添加节点数据
    virtual void AddNodeData(Node_Content& node);
    //添加界面更新组件
    virtual void AddData(int x,int y);
    virtual void Set_Current_Index(XSTATUS sta);
    virtual XSTATUS Get_Current_Data();

    /*通知视图控件进行update*/
    virtual void NotfyAll();
    //将当前的模型赋值为NULL
    virtual void SetModel();
    //添加路线
    virtual int Get_route_count();
    virtual void Add_Route(int num);
    virtual void Delete_Route(int num);
    virtual void Get_route(int num);
    virtual void Sort_Route_node();
    virtual int Find_Route_node(int index);
    virtual void Remove_Route_node();
    virtual void Add_Route_ndoe();
    std::vector<Route_node>* curren_route;
    XModel *m;
protected:
    IView *v = 0;
    IControllerFactroy* factroy;
    /*队列的方式存储对应的线路_map结构存储对应的数据*/
    std::map<int,std::vector<Route_node>*> route_map;
    //所有的节点表
    std::vector<XModel*> m_task;
    XSTATUS current_index = XPEN;
    Builder* Export;
    Ioperator* oper_do;
};

#endif // ICONTROLLER_H
