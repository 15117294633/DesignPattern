#include "XModel.h"
#include "IController.h"
XModel::XModel()
{
    context=new Node_Content();
}
XModel::XModel(int x,int y)
{
    this->x_pos=x;
    this->y_pos=y;
}
void XModel::update_context(Node_Content& con)
{
     qDebug()<<"model()";
    *(this->context)=con;
}
void XModel::Add(X_Pos pos,int type)
{
    /*根据不同的策略来添加数据*/
   this->x_pos=pos.x;
   this->y_pos=pos.y;
    /*更新pos的val*/
}
bool XModel::operator < (const XModel& m)
{
    return this->id<m.id;
}
bool XModel::operator == (const XModel& model)
{
    int r=(this->x_pos-model.x_pos)*(this->x_pos-model.x_pos)+
            (this->y_pos-model.y_pos)*(this->y_pos-model.y_pos);
    if(r<=abs_dis)
    {
        return true;
    }else
    {
        return false;
    }
}
XModel& XModel::operator = (const XModel& obj)
{
    if(this!=&obj)
    {
        this->type=obj.type;
        this->x_pos=obj.x_pos;
        this->y_pos=obj.y_pos;
    }
    return *this;
}
XModel::~XModel()
{


}
