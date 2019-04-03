#ifndef IVIEW_H
#define IVIEW_H
#include "IObserver.h"
class IView:public IObserver
{
   public:
    virtual void InitDevice(void *d) = 0;

    virtual bool InitBack(const char *url) = 0;

        //绘制out结果
    virtual void Paint() = 0;

};
#endif // IVIEW_H
