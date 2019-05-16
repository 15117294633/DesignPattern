#ifndef DOADDROUTE_H
#define DOADDROUTE_H
#include "ioperator.h"
class DoAddRoute:public Ioperator
{
public:
    static Ioperator* Get_Obj()
    {
        static  DoAddRoute obj;
        return &obj;
    }
    void Do_operator(int x,int y);
    DoAddRoute();
};

#endif // DOADDROUTE_H
