#include "XCircleGraph.h"
#include "XModel.h"
#include <QPainter>
#include <QPen>
#include <QColor>
void  XCircleGraph::Draw(XModel *m)
{
    if (!painter || !img)return;

    QPen pen; //画笔
    pen.setWidth(5);
    pen.setColor(QColor(200, 0, 0));

    int size =m->pos.size();

    painter->drawEllipse(m->pos[size-1].x,m->pos[size-1].y,10,10);

}
