#include "XCircleGraph.h"
#include "XModel.h"
#include <QPainter>
#include <QPen>
#include <QColor>
#include <QDebug>
void  XCircleGraph::Draw(XModel *m)
{
    if (!painter || !img)return;

    QPen pen; //画笔
    pen.setWidth(3);
    pen.setColor(QColor(200, 0, 0));
    if(m->color==1)
    {
       pen.setColor(QColor(255,255, 0));
    }
    painter->setPen(pen);
    painter->drawEllipse(QPointF(m->x_pos,m->y_pos),15,15);
    /*画一个文本的矩形*/
    qDebug()<<m->id;
    painter->drawText(QPointF(m->x_pos-4,m->y_pos+2),QString::number(m->id, 10));

}
