#ifndef ICONTROLLER_H
#define ICONTROLLER_H
class XModel;
class IView;
#include "IControllerFactroy.h"
#include "vector"

enum XSTATUS
{
    XPEN,
    XERASER,
    XRECT,
    XIMAGE,
    XCIRCLE
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
    /*添加模型*/
    virtual void AddModel(int s=-1);
    virtual void AddData(int x,int y);
    virtual void Set_Current_Index(XSTATUS sta);
    virtual void NotfyAll();
protected:
    IView *v = 0;
    XModel *m = 0;
    IControllerFactroy* factroy;
    std::vector<XModel*> m_task;
    XSTATUS current_index = XPEN;
};

#endif // ICONTROLLER_H
