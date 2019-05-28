#include "QObject"
#include "IController.h"
#include "iview.h"
#include "XModel.h"
#include "QDebug"
#include "vector"
#include "TxtBuild.h"
#include "Do_move.h"
#include "DoAddRoute.h"
#include "QFileDialog"
#include "SqlLite_Helper.h"
#include "XmlHelper.h"
#include "iniFilePath.h"
#include "Route_Id_Man.h"
#include <QList>
#include <QDir>
IController::IController()
{
   /*选择导出方式,后期加入配置选项*/
    Export=new TxtBuild();
    int num;
    iniFilePath::Get_Obj()->Read_from_Ini(num);
    this->Set_Bit(num);
    sql=SqlLite_Helper::Get_Obj();
    Route_Id_Man::Get_Obj()->Load_All_Bits();
}
void IController::Load_Data_From_Sql()
{
    int size=this->m_task.size();
    for(int i=1;i<size;i++)
    {
        sql->FindNodeData(*m_task.at(i)->context,i);
    }
}
void IController::Load_Data_From_Xml()
{
    XmlHelper::Get_Obj()->Load_Data_From_Xml();
    NotfyAll();
}
void IController::Load_Route_Node()
{
    QDir dir;
    if(dir.exists("route"))
    {
        dir.cd("route");
        QStringList list=dir.entryList();
        for(int i=0;i<list.count();i++)
        {
            QString file_name=list.at(i);

            if(file_name.startsWith("route"))
            {
                int num=file_name.mid(5,1).toInt();
                Add_Route(num);
                QString folder_name=QString("route/%1").arg(file_name);
                QFile file(folder_name);
                if( file.open(QIODevice::ReadOnly | QIODevice::Text) )
                {
                    QTextStream in(&file);
                    in.readLine();
                    while( !in.atEnd() )
                    {
                       int id=in.readLine().left(3).toInt();
                       Route_node node;
                       node.id=id;
                       this->curren_route->append(node);
                    }
                    file.close();
                }
            }
        }
    }
}
IController::~IController()
{


}
//生成对应的对象工厂
IController* IController::Create(IControllerFactroy *f)
{
    if (!f)return 0;
    IController *c = f->CreateC();
    XmlHelper::Get_Obj()->Set_Controller(c);
    c->v = f->CreateV();
    c->factroy=f;
    return c;
}
void IController::InitDevice(void *d)
{
    AddModel(XIMAGE);
    this->Load_Data_From_Xml();
    this->Load_Data_From_Sql();
    this->Load_Route_Node();
    this->Sort_Route_node();
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
   if(s<0)    s=this->current_index;
   this->m = factroy->CreateM();
   int size=this->m_task.size();
   this->m->id=size;
   if(size==0)
   {
       this->m->id=size;
   }
   if(size>=1)
   {
       this->m->id=Route_Id_Man::Get_Obj()->Get_Route_Id();
   }
   this->m->type=s;
   this->m->color=0;
   this->m->Attach(this->v);
   this->m_task.push_back(m);
   //进行排序
   if(size>=2)
   {
      Sort_Route_node();
   }
   /*新增一个节点*/
   if(size>=1)
   {
      X_Pos pos(0,0);
      XmlHelper::Get_Obj()->AddXml(&pos,this->m->id,0);
   }

}
//删除最后一个模型
void IController::RemoveModel()
{
    if(this->m_task.size()>1)
    {
      //使用迭代器删除
        std::vector<XModel*>::iterator iter;
        for(iter=m_task.begin();iter!=m_task.end();)
        {
            if((*iter)->id==m->id)
            {
                 //删除对应route节点元素中的数据
                std::map<int,QList<Route_node>*>::iterator iter_map=route_map_list.begin();
                for(;iter_map !=route_map_list.end();iter_map++)
                {
                    QList<Route_node>* cur_route_node=iter_map->second;
                    int size=cur_route_node->size();
                    for(int i=0;i<size;i++)
                    {
                        if(cur_route_node->at(i).id==m->id)
                        {
                            qDebug()<<"index is:"<<i<<"size"<<cur_route_node->size();
                            cur_route_node->removeAt(i);
                            break;
                        }
                    }
                }
                 //删除任务节点里面的数据
                 iter=this->m_task.erase(iter);
            }
            else
            {
                iter++;
            }
        }
      //xml表中删除
      XmlHelper::Get_Obj()->RemoveXml(m->id,0);
      //配置表中删除
      Route_Id_Man::Get_Obj()->Clear_Route_Id(m->id);
    }
    if(m_task.size()>=2)
    {
       Sort_Route_node();
    }
    NotfyAll();
    this->update_c();
}
void IController::AddNodeData(Node_Content& node)
{
    //更新数据到模型层
     //Export->builderData(&node);
     this->m->update_context(node);
     //更新至数据库中
     if(sql->Has_Id(this->m->id))//有数据元素的时候
     {
        sql->ModifiNode(&node);
     }
     else//创建该节点并插入到表中
     {
         sql->InsertIntoData(&node);
     }
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
void IController::update_c()
{
    this->v->Do_Update();
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
//节点相关的操作
void IController::Add_Route()
{
   QList<Route_node>* route=new QList<Route_node>();

   this->curren_route=route;

   int index=this->Get_Bit_Unused();
    this->m_current_route=index+1;//route1-route(index+1)
    if(index!=-1)
    {
        //遍历查找对应的下标 后期再改
        qDebug()<<"add route"<<index+1;

        XmlHelper::Get_Obj()->Add_Xml_Route(index+1);
        route_map_list.insert(std::make_pair(index+1,route));
        //更新对应的节点
        Show_ALL_Node();
    }
    else
    {

    }

}
void IController::Add_Route(int num)
{

    QList<Route_node>* route=new QList<Route_node>();
    this->curren_route=route;
    if(num!=-1)
    {
        route_map_list.insert(std::make_pair(num,route));
    }
    else
    {

    }
}
void IController::Delete_Route(int num)
{
    std::map<int,QList<Route_node>*>::iterator iter=route_map_list.begin();
    for(;iter !=route_map_list.end();iter++)
    {
        if(iter->first==num)
        {
            XmlHelper::Get_Obj()->Remove_Xml_Route(num);
            this->clear_bit(num-1);
            delete iter->second;
            route_map_list.erase(iter);
        }
    }
}
void IController::Get_route(int num)
{
    this->curren_route=route_map_list[num];
    /*根据节点比对更改相关val*/
    int size_a=m_task.size();
    for(int i=0;i<size_a;i++)
    {
        this->m_task[i]->color=0;
    }
    int size=curren_route->size();
    for(int i=0;i<size;i++)
    {
        this->m_task.at(curren_route->at(i).id)->color=1;
    }
    NotfyAll();
    this->update_c();
}
void IController::Edit_route(int num)
{
    this->m_current_route=num;
    Get_route(num);
}
void IController::Show_ALL_Node()
{
    int size=m_task.size();
    for(int i=0;i<size;i++)
    {
        this->m_task[i]->color=0;
    }
    NotfyAll();
}
int IController::Find_Route_node_before()
{
    int ret=-1;
    int size=this->curren_route->size();
    for(int i=0;i<size;i++)
    {
        if(curren_route->at(i).id==m->id)
        {
            if(i==0)
            {
               ret=0;
            }
            else
            {
                ret=curren_route->at(i-1).id;
            }
            break;
        }
    }
    return ret;
}
void IController::Sort_Route_node()
{
    int len=m_task.size();
    bool exchange=true;
    for(int i=0;i<len&&exchange==true;i++)
    {
        exchange=false;
        for(int j=len-1;j>i;j--)
        {
            if( m_task[j]->id<m_task[j-1]->id)
            {
                XModel* temp=m_task[j];
                m_task[j]=m_task[j-1];
                m_task[j-1]=temp;
                exchange=true;
            }
        }
    }
}
int IController::Find_Route_node(int index)
{
    int ret=-1;
    if(curren_route!=nullptr)
    {
        for (int i = 0; i < curren_route->size();i++)
        {
            qDebug()<<"Current_route id:"<<curren_route->at(i).id<<"index:"<<index;
            if (curren_route->at(i).id ==index)
            {
                ret=i;
                break;
            }
        }
    }
    return ret;
}
void IController::Remove_Route_node()
{
    if(this->curren_route!=nullptr)
    {
        /*将当前的元素加入到数组里面*/
         int ret=Find_Route_node(m->id);
         if(ret!=-1)
         {
            XmlHelper::Get_Obj()->RemoveXml(this->m->id,this->m_current_route);
            m->color=0;
            this->curren_route->removeAt(ret);
         }
         else
         {
             qDebug()<<"该数据点不存在";
         }
        NotfyAll();
    }
}
bool IController::Add_Route_node()
{
   return Add_Route_node(this->m->id);
}
bool IController::Add_Route_node(int num)
{
    Route_node node;
    node.id=m->id;
    m->color=0;
    int ret;
    qDebug()<<"num"<<num;
    if(num==0)
    {
       ret=0;
    }
    else
    {
       ret=Find_Route_node(num);
       num=ret+1;
    }
    if(ret==-1)
    {
        qDebug()<<"插入元素失败";
        return 0;
    }
    ret=Find_Route_node(m->id);
    if(ret==-1)
    {
      X_Pos pos(0,0);
      XmlHelper::Get_Obj()->AddXml(&pos,m->id,this->m_current_route);
      m->color=1;
      curren_route->insert(num,node);
      qDebug()<<"插入元素"<<this->m->id<<"下标:"<<num;
    }
    else
    {
        qDebug()<<"当前元素已存在"<<this->m->id;
    }
    NotfyAll();
    update_c();
    return 1;
}
int IController::Get_route_count()
{
    return  route_map_list.size();
}
void IController::Set_Current_Index(XSTATUS sta)
{
    this->current_index=sta;
}
XSTATUS IController::Get_Current_Data()
{
    return this->current_index;
}
/*位图相关的操作*/
int IController::Get_Bit_Unused()
{
    int index=0;
    for(int i=0;i<16;i++)
    {
        if(!(m_route_used&(1<<i)))
        {
            m_route_used|=1<<i;
            //val写入
            iniFilePath::Get_Obj()->Write_to_Ini(m_route_used);
            return index;
        }
        else
        {
             index++;
        }
    }
    return -1;
}
void IController::Set_Bit(int value)
{
   m_route_used=value;
}
void IController::clear_bit(int n)
{
    //clear对应的位置
    m_route_used&=~(1<<n);
    iniFilePath::Get_Obj()->Write_to_Ini(m_route_used);
}
My_Sql* IController:: Get_Sql()
{
    return this->sql;
}
void  IController::import_route(QString fileName)
{
    //场馆坐标点到处
    QString tar_loc=QString("/pointer.txt");
    QString name_loc=fileName+tar_loc;
    QFile file1(name_loc);
    if( file1.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        QTextStream out1(&file1);
        int loc_size;
        loc_size=this->m_task.size();
        out1<<QString("num:%1").arg(loc_size-1)<<endl;
        for(int i=1;i<loc_size;i++)
        {
            QString Pointer=QString("(%1,%2)").arg(this->m_task[i]->x_pos).arg(this->m_task[i]->y_pos);
            out1<<Pointer<<endl;
        }
    }
    file1.close();

    //路线导出
    std::map<int,QList<Route_node>*>::iterator iter=route_map_list.begin();
    for(;iter !=route_map_list.end();iter++)
    {
        QList<Route_node>* cur_route;
        cur_route=iter->second;
        QString name=QString("/route%1.txt").arg(iter->first);
        QString path=fileName+name;
        qDebug()<<"current path:"<<path;
        bool ret = true;
        QFile file(path);
        if( file.open(QIODevice::WriteOnly | QIODevice::Text) )
        {
             QTextStream out(&file);
             int size=cur_route->size();
             QString head_first=QString("route%1:%2").arg(iter->first).arg(size);
             out<<head_first<<endl;
             for(int i=0;i<size;i++)
             {
                out<<Export->builderData(this->m_task[cur_route->at(i).id]->context)<<endl;
             }
            file.close();
        }
    }
}
void IController::NotfyAll()
{
    int size=m_task.size();
    for(int i=0;i<size;i++)
    {
        m_task[i]->Notify();
    }
}
