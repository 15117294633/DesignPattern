#include "XRectGraph.h"
#include "XModel.h"
#include <QPainter>
#include <QPen>
void XRectGraph::Draw(XModel *m)
{
    if (!painter || !m)return;
    QPen pen; //画笔
    pen.setWidth(5);
    pen.setColor(QColor(200, 0, 0));
    //设置连接处
    pen.setCapStyle(Qt::RoundCap); //顶部样式
    pen.setJoinStyle(Qt::RoundJoin);//连接处样式

                                    //设置抗锯齿
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(pen);
    int size = m->pos.size();
    if (size < 2)return;
    //从起始点到结尾画矩形
    int x = m->pos[0].x;
    int y = m->pos[0].y;
    int w = m->pos[size - 1].x - x;
    int h = m->pos[size - 1].y - y;
    painter->drawRect(x,y,w,h);

}
