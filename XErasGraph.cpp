#include "XErasGraph.h"
#include "QPen"
#include "XModel.h"
#include "QPainter"

XErasGraph::XErasGraph()
{

}
void XErasGraph::Draw(XModel *m)
{

    if (!painter || !img)return;

    QPen pen; //画笔
    pen.setWidth(5);

        //设置连接处
    pen.setCapStyle(Qt::RoundCap); //顶部样式
    pen.setJoinStyle(Qt::RoundJoin);//连接处样式

    pen.setBrush(*img);
        //设置抗锯齿
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(pen);
    int size =m->pos.size();
    for (int i = 1; i < size; i++)
    {
        painter->drawLine(QLine(m->pos[i - 1].x, m->pos[i - 1].y, m->pos[i].x, m->pos[i].y));
    }
}
