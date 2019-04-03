#ifndef ICONTROLLERFACTROY_H
#define ICONTROLLERFACTROY_H
class XModel;
class IView;
class IController;
class IControllerFactroy
{
public:
    virtual XModel *CreateM()=0;
    virtual IView *CreateV()=0;
    virtual IController *CreateC() = 0;
};

#endif // ICONTROLLERFACTROY_H
