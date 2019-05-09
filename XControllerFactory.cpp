#include "XControllerFactory.h"

#include "XModel.h"
#include "IController.h"
#include "XEditView.h"
#include "XPenGraph.h"
#include "XErasGraph.h"
#include "xrectgraph.h"
#include "XImageGraph.h"
#include "XCircleGraph.h"
XControllerFactory::XControllerFactory()
{

}
XModel *XControllerFactory::CreateM()
{
    return new XModel();
}
IView *XControllerFactory::CreateV()
{
    //注册对应的时间
    XEditView::Get_Obj()->RegView<XPenGraph>(XPEN);
    XEditView::Get_Obj()->RegView<XErasGraph>(XERASER);
    XEditView::Get_Obj()->RegView<XRectGraph>(XRECT);
    XEditView::Get_Obj()->RegView<XImageGraph>(XIMAGE);
    XEditView::Get_Obj()->RegView<XCircleGraph>(XCIRCLE);
    return XEditView::Get_Obj();
}
IController *XControllerFactory::CreateC()
{
    return new IController();
}
XControllerFactory::~XControllerFactory()
{
}
