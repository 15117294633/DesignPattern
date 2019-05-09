#ifndef XMODEL_H
#define XMODEL_H
#include "XSubject.h"
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

class XModel:public XSubject
{
public:
    /*里面有一个类用于存放*/
    std::vector<X_Pos> pos;
    void Add(X_Pos pos);
    XModel();
    ~XModel();
};

#endif // XMODEL_H
