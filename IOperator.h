#ifndef IOPERATOR_H
#define IOPERATOR_H
class IController;
class Ioperator
{
protected:
    IController* con;
public:
    //暂时加入这一个元素
    virtual void Do_operator(int x,int y)=0;
    void set_data(IController* con)
    {
        this->con=con;
    }
};
#endif // IOPERATOR_H
