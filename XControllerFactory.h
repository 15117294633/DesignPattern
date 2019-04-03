#ifndef XCONTROLLERFACTORY_H
#define XCONTROLLERFACTORY_H
#include "IControllerFactroy.h"
class XControllerFactory:public IControllerFactroy
{
public:
    static XControllerFactory *Get()
    {
        static XControllerFactory f;
        return &f;
    }
    XControllerFactory();
    ~XControllerFactory();
    virtual XModel *CreateM();
    virtual IView *CreateV();
    virtual IController *CreateC();

};

#endif // XCONTROLLERFACTORY_H
