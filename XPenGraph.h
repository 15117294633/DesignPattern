#ifndef XPENGRAPH_H
#define XPENGRAPH_H
#include "IGraph.h"
class XPenGraph:public IGraph
{
public:
    void  Draw(XModel *m);
    XPenGraph();
};

#endif // XPENGRAPH_H
