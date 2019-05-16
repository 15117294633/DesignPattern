#ifndef DO_MOVE_H
#define DO_MOVE_H
#include "ioperator.h"
class Do_move : public Ioperator
{
public:
    void Do_operator(int x,int y);
    Do_move();
};

#endif // DO_MOVE_H
