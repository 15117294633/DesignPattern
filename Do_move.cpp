#include "Do_move.h"
#include "IController.h"
Do_move::Do_move()
{

}
void Do_move::Do_operator(int x,int y)
{
    if(con->m!=nullptr)
    {
       con->AddData(x,y);
    }
    else
    {
       con->Is_Valid_Point(x,y);
    }
}
