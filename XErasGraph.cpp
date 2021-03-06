﻿#include "XErasGraph.h"
#include "XModel.h"
#include <QPainter>
#include <QPen>
void XErasGraph::Draw(XModel *m)
{
    if (!painter || !m)return;
    QPen pen; //画笔
    pen.setWidth(5);
    //设置连接处
    pen.setCapStyle(Qt::RoundCap); //顶部样式
    pen.setJoinStyle(Qt::RoundJoin);//连接处样式
    //用原图做刷子
    pen.setBrush(*img);
                                    //设置抗锯齿
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(pen);
    int size = m->pos.size();
    for (int i = 1; i < size; i++)
    {
        //绘制线，开始点到结束点
        painter->drawLine(QLine(m->pos[i - 1].x, m->pos[i - 1].y, m->pos[i].x, m->pos[i].y));
    }

}
