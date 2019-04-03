#include "XControllerFactory.h"

#include "XModel.h"
#include "IController.h"
#include "XEditView.h"
#include "XPenGraph.h"
#include "XErasGraph.h"
XControllerFactory::XControllerFactory()
{

}
XModel *XControllerFactory::CreateM()
{
    return new XModel();
}
IView *XControllerFactory::CreateV()
{
    XEditView::Get_Obj()->RegView<XPenGraph>(XPEN);
    XEditView::Get_Obj()->RegView<XErasGraph>(XERASER);
    return XEditView::Get_Obj();
}
IController *XControllerFactory::CreateC()
{
    return new IController();
}
XControllerFactory::~XControllerFactory()
{
}
