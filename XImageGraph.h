﻿#ifndef XIMAGEGRAPH_H
#define XIMAGEGRAPH_H
#include "IGraph.h"
class XImageGraph :
    public IGraph
{
public:
    virtual void Draw(XModel *m);
};
#endif // XIMAGEGRAPH_H
