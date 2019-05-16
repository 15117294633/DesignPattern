
#include "IController.h"
#include "iview.h"
#include "XModel.h"
#include "QDebug"
#include "vector"
#include "TxtBuild.h"
#include "Do_move.h"
#include "DoAddRoute.h"
#include "DoRemoveRoute.h"
IController::IController()
{
   /*选择导出方式,后期加入配置选项*/
    Export=new TxtBuild();
}

IController::~IController()
{


}
//生成对应的对象工厂
IController* IController::Create(IControllerFactroy *f)
{
    if (!f)return 0;
    IController *c = f->CreateC();
    c->v = f->CreateV();
    c->factroy=f;
    return c;
}
void IController::InitDevice(void *d)
{
    AddModel(XIMAGE);
    this->v->InitDevice(d);
}
bool IController::InitBack(const char *url)
{
    return  this->v->InitBack(url);
}
void IController::Paint()
{
     this->v->Paint();
}
void IController::AddModel(int s)
{
    /*添加一个对应的Model*/
    if(s<0)    s=this->current_index;
   this->m = factroy->CreateM();
   int size=this->m_task.size();
   this->m->id=size;
   this->m->type=s;
   this->m->color=0;
   this->m->Attach(this->v);
   this->m_task.push_back(m);
}
void IController::AddNodeData(Node_Content& node)
{
    //更新数据到模型层
     qDebug()<<"model level";
     Export->builderData(&node);
     this->m->update_context(node);
}
void IController::AddData(int x,int y)
{
    if(!m) return;
    this->m->Add(X_Pos(x,y),current_index);
    NotfyAll(); //只通知注册
}
void IController::SetModel()
{
     this->m=nullptr;
}
 void  IController::do_contral(int x,int y)
 {

     switch(this->current_index)
     {
        case XMOVE:
        /*遍历相关的index*/
         oper_do=new Do_move();
         oper_do->set_data(this);
         oper_do->Do_operator(x,y);
        break;
        case XCIRCLE:
           this->AddData(x,y);
        break;
        case XADDROUTE:
         DoAddRoute::Get_Obj()->set_data(this);
         DoAddRoute::Get_Obj()->Do_operator(x,y);
        break;

        case XDELETROUTE:
         DoRemoveRoute::Get_Obj()->set_data(this);
         DoRemoveRoute::Get_Obj()->Do_operator(x,y);
        break;
     }

 }
bool  IController::Is_Valid_Point(int x,int y)
{
    bool ret=false;
    for(std::vector<XModel*>::iterator iter=m_task.begin();iter!=m_task.end()&&!ret;++iter)
    {
           if(*(*iter)==XModel(x,y))
           {
               /*进行对选中元素的移动*/
               qDebug()<<"find data";
               /*重载赋值操作符*/
               this->m=*iter;
               ret=true;
           }
    }
    return ret;
}
void IController::Add_Route(int num)
{
    std::vector<Route_node>* route=new  std::vector<Route_node>();
    this->curren_route=route;
    route_map.insert(make_pair(num,route));
}
void IController::Delete_Route(int num)
{

    std::map<int,std::vector<Route_node>*>::iterator iter=route_map.begin();
    for(;iter !=route_map.end();iter++)
    {
        if(iter->first==num)
        {
            delete iter->second;
            route_map.erase(iter);
        }
    }
}
void IController::Sort_Route_node()
{
   std::sort(curren_route->begin(),curren_route->end());
}
int IController::Find_Route_node(int index)
{
     int low = 0;
     int high = curren_route->size()-1;
         while(low <= high) {
            int middle = (low + high)/2;
            if(index == curren_route->at(middle).id) {
                 return middle;
            }else if(index <curren_route->at(middle).id) {
                 high = middle - 1;
             }else {
                 low = middle + 1;
             }
        }
        return -1;

//  return std::binary_search(curren_route->begin(),curren_route->end(),m->id);
}
void IController::Remove_Route_node()
{
    if(this->curren_route!=nullptr)
    {
        /*将当前的元素加入到数组里面*/
        Route_node node;
        node.id=m->id;

        qDebug()<<"查找到元素"<<this->m->id;

        /*排序*/
        Sort_Route_node();
        NotfyAll();
    }
}
void IController::Add_Route_ndoe()
{
    Route_node node;
    node.id=m->id;
    m->color=0;
    int ret=Find_Route_node(m->id);
    if(ret=-1)
    {
      m->color=1;
      curren_route->push_back(node);
      qDebug()<<"插入元素"<<this->m->id;
    }

    /*排序*/
    Sort_Route_node();
    NotfyAll();
}
void IController::Get_route(int num)
{
    this->curren_route=route_map[num];
}
int IController::Get_route_count()
{
    return this->route_map.size();
}
void IController::Set_Current_Index(XSTATUS sta)
{
    qDebug()<<sta<<endl;
    this->current_index=sta;
}
XSTATUS IController::Get_Current_Data()
{
    return this->current_index;
}
void IController::NotfyAll()
{
    int size=m_task.size();
    for(int i=0;i<size;i++)
    {
        m_task[i]->Notify();
    }
}
