#include "DoAddRoute.h"
#include "IController.h"
#include "XModel.h"
#include "QDebug"
DoAddRoute::DoAddRoute()
{

}
 void DoAddRoute::Do_operator(int x,int y)
 {
    /*加入节点*/
    //之前肯定已经创建了一个节点,只需要加入到当前的路径
     if(this->con->m==nullptr)
     {
         //弹出菜单
         this->con->Is_Valid_Point(x,y);
     }
     else
     {
         if(con->curren_route!=nullptr)
         {
             /*将当前的元素加入到数组里面*/
             Route_node node;
             node.id=this->con->m->id;
             this->con->m->color=1;
             qDebug()<<"查找到元素"<<this->con->m->id;
             con->curren_route->push_back(node);
             /*排序*/
             con->Sort_Route_node();
             con->NotfyAll();
         }
     }
 }
