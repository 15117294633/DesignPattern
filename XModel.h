#ifndef XMODEL_H
#define XMODEL_H
#include "XSubject.h"
#define abs_dis 10*10
/*对应的位置info*/
struct X_Pos
{
    X_Pos(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    int x = 0;
    int y = 0;
};
class Node_Content;
//实际的业务逻辑是在模型层去做
class XModel:public XSubject
{
private:
    Node_Content* context;
public:
    int type;
    int id;
    int x_pos;//控件的中心点x坐标
    int y_pos;//控件的中心点y坐标
    int color;//对应路线的颜色数据
    /*里面有一个类用于存放*/
    std::vector<X_Pos> pos;
    void Add(X_Pos pos,int type);
    bool operator == (const XModel& model);
    XModel& operator = (const XModel& obj);
    /*更新对应的context数据*/
    void update_context(Node_Content& con);
    XModel();
    XModel(int x,int y);
    ~XModel();
};

#endif // XMODEL_H
