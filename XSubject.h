#ifndef XSUBJECT_H
#define XSUBJECT_H
#include "vector"
class IObserver;
class XSubject
{
public:
    virtual void Notify();
    void Attach(IObserver *ob);
 protected:
    std::vector<IObserver*> Obs;

};

#endif // XSUBJECT_H
