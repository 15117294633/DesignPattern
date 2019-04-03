#ifndef XERASGRAPH_H
#define XERASGRAPH_H
#include "IGraph.h"
class XErasGraph:public IGraph
{
public:
    XErasGraph();
    void Draw(XModel *m);
};

#endif // XERASGRAPH_H
