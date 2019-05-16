﻿#include "TxtBuild.h"
//改进数据头单独放置于一个文件
#include "IController.h"
#include "QDebug"
//节点号 类型 操作 操作内容 站点转向 转向的角度 场馆控制 设备类型 节点的描述信息
//001    01  01   002      01    090        01      00 D5E2CAC7B5DAB6FEB8F6D1DDCABEB5C4C0FDD7D3
TxtBuild::TxtBuild()
{
    this->con.clear();
}
void TxtBuild::builderData(Node_Content* content)
{
   this->con.clear();
   QString temp;
   //001
   if((0<=content->node_id)&&(content->node_id<10))
   {
       temp=QString("%1%2").arg("00").arg(content->node_id);
   }
   else if((10<=content->node_id)&&(content->node_id<99))
   {
        temp=QString("%1%2").arg("0").arg(content->node_id);
   }
   else if((100<=content->node_id)&&(content->node_id<999))
   {
        temp=QString("%1%2").arg("").arg(content->node_id);
   }
   //拼接头部
    con.append(temp);
    con.append(' ');
    temp.clear();
    //类型 01
    temp=QString("%1%2").arg("0").arg(content->type);
    con.append(temp);
    con.append(' ');
    temp.clear();
    //操作 01
    temp=QString("%1%2").arg("0").arg(content->Operator);
    con.append(temp);
    con.append(' ');
    temp.clear();
    //操作内容 001.MP4 后期有需求在变更
    if((0<=content->node_id)&&(content->node_id<10))
    {
        temp=QString("%1%2").arg("00").arg(content->node_id);
    }
    else if((10<=content->node_id)&&(content->node_id<99))
    {
         temp=QString("%1%2").arg("0").arg(content->node_id);
    }
    else if((100<=content->node_id)&&(content->node_id<999))
    {
         temp=QString("%1%2").arg("").arg(content->node_id);
    }
     con.append(temp);
     con.append(' ');
     temp.clear();
     //站点转向01
     temp=QString("%1%2").arg("0").arg(content->dir);
     con.append(temp);
     con.append(' ');
     temp.clear();
     //转向角
     if((0<=content->dir_angle)&&(content->dir_angle<10))
     {
         temp=QString("%1%2").arg("00").arg(content->dir_angle);
     }
     else if((10<=content->dir_angle)&&(content->dir_angle<99))
     {
          temp=QString("%1%2").arg("0").arg(content->dir_angle);
     }
     else if((100<=content->dir_angle)&&(content->dir_angle<999))
     {
          temp=QString("%1%2").arg("").arg(content->dir_angle);
     }
      con.append(temp);
      con.append(' ');
      temp.clear();

     con.append(' ');
     //设备使能
     temp=QString("%1%2").arg("0").arg(content->Equ_Sta);
     con.append(temp);
     con.append(' ');
     temp.clear();
     //设备类型
     temp=QString("%1%2").arg("0").arg(content->type);
     con.append(temp);
     con.append(' ');
     temp.clear();
     //场馆节点描述信息
     int len=content->Desc.length();
     con.append(ByteArrayToHexString(content->Desc));
     for(int i=len;i<20;i++)
     {
        con.append(' ');
     }
     qDebug()<<con;
}

QString TxtBuild::ByteArrayToHexString(QByteArray data){

    QString ret(data.toHex().toUpper());
    int len = ret.length()/2;
    qDebug()<<len;
    ret.insert(0,"");
    for(int i=1;i<len;i++)
    {
        ret.insert(4*i+i-1,"");//编写格式
    }
    return ret;
}
