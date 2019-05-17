#ifndef XEDITVIEW_H
#define XEDITVIEW_H
#include "QImage"
#include <vector>
#include <IObserver.h>
#include <IView.h>
#include <map>
#include <IGraph.h>
class QLabel;
class QWidget;
/*数据类型对象*/
class QPainter;
using namespace std;
class XEditView:public IView
{
public:
    static XEditView* Get_Obj()
    {
        static  XEditView obj;
        return &obj;
    }
    /*初始化设备*/
    virtual void InitDevice(void *d);
    //载入背景图
    virtual bool InitBack(const char *url);
    //绘制结果
    virtual void Paint();

    virtual void Update(XSubject *sub);

    virtual void Do_Update();
    template<class ViewClass>
    IGraph *RegView(int type)
    {
        ViewClass *view = new ViewClass();
        views.insert(make_pair(type, view));
        return view;
    }
     ~XEditView();
 protected:
    XEditView();
    QWidget *device;
    QImage src;
    /*缓冲作用*/
    QImage out;
    QPainter* painter=nullptr;
    std::map<int,IGraph*> views;
};

#endif // XEDITVIEW_H
