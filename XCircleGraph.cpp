#include "XCircleGraph.h"
#include "XModel.h"
#include <QPainter>
#include <QPen>
#include <QColor>
#include <QDebug>
void  XCircleGraph::Draw(XModel *m)
{

    qDebug()<<"color:"<<m->color<<m->id<<":"<<"("<<m->x_pos<<":"<<m->y_pos<<")";
    if (!painter || !img)return;

    QPen pen; //画笔
    pen.setWidth(2);
    pen.setColor(QColor(0, 0, 255));
    if(m->color==1)
    {
       pen.setColor(QColor(255,255, 0));
    }
    painter->setPen(pen);
    painter->drawEllipse(QPointF(m->x_pos,m->y_pos),15,15);
    /*画一个文本的矩形*/
    pen.setWidth(10);
    QFont font = painter->font();
    font.setPixelSize(15);
    painter->setFont(font);

    painter->setPen(pen);
    painter->drawText(QPointF(m->x_pos-4,m->y_pos+2),QString::number(m->id, 10));

}
