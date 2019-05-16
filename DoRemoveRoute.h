#ifndef DOREMOVEROUTE_H
#define DOREMOVEROUTE_H
#include "ioperator.h"
class DoRemoveRoute:public Ioperator
{
public:
    static Ioperator* Get_Obj()
    {
        static  DoRemoveRoute obj;
        return &obj;
    }
    void Do_operator(int x,int y);
    DoRemoveRoute();
};

#endif // DOREMOVEROUTE_H
