#include "XSubject.h"
#include "IObserver.h"
#include "vector"
void XSubject::Notify()
{
    for(int i=0;i<Obs.size();i++)
    {
       Obs[i]->Update(this);
    }
}
void  XSubject::Attach(IObserver *ob)
{
    this->Obs.push_back(ob);
}

