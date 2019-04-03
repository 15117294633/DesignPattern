#include "IController.h"
#include "iview.h"
#include "XModel.h"
#include "QDebug"
IController::IController()
{

}

IController::~IController()
{


}
//生成对应的对象工厂
IController* IController::Create(IControllerFactroy *f)
{
    if (!f)return 0;
    IController *c = f->CreateC();
    //c->m = f->CreateM();
    c->v = f->CreateV();
    c->factroy=f;
    return c;
}
void IController::InitDevice(void *d)
{
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
void IController::AddModel()
{
    /*添加一个对应的Model*/
   this->m = factroy->CreateM();
    //注册到
   this->m->type=current_index;
   this->m->Attach(this->v);
   this->m_task.push_back(m);
}
void IController::AddData(int x,int y)
{
    this->m->Add(X_Pos(x,y));
}
void IController::Set_Current_Index(XSTATUS sta)
{
    qDebug()<<sta<<endl;
    this->current_index=sta;
}
