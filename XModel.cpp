#include "XModel.h"

XModel::XModel()
{

}
void XModel:: Add(X_Pos pos)
{
    this->pos.push_back(pos);
    /*通知对应的观察者更新*/
    this->Notify();
}
XModel::~XModel()
{


}
