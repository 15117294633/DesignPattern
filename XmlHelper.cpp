#include "XmlHelper.h"
#include <QDomDocument>
#include <XModel.h>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <IController.h>
#include <IObserver.h>
#include <iview.h>
void  XmlHelper::Set_Controller(IController* c)
{
    this->Controller=c;
}
void XmlHelper::Load_Data_From_Xml()
{
    Read_Xml(0);
}
void XmlHelper::Write_Xml()
{
   QFile file("test.xml");
   if(!file.open(QFile::WriteOnly|QFile::Truncate))
           return;
   QDomDocument doc;
   QDomProcessingInstruction instruction;
   instruction=doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
   doc.appendChild(instruction);
   QDomElement root=doc.createElement("content");
   doc.appendChild(root);

   QDomElement route=doc.createElement("route");
   route.setAttribute("type",0);
   root.appendChild(route);
   //写入至文件
   QTextStream out_stream(&file);
   doc.save(out_stream,4); //缩进4格
   file.close();

}

void XmlHelper::Add_Xml_Route(int id)
{
    QFile file("test.xml"); //相对路径、绝对路径、资源路径都可以
    if(!file.open(QFile::ReadOnly))
        return;
    QDomDocument doc;
    if(!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();

    QDomElement root=doc.documentElement();
    QDomElement route=doc.createElement("route");
    route.setAttribute("type",id);
    root.appendChild(route);

    if(!file.open(QFile::WriteOnly|QFile::Truncate))
        return;
    QTextStream out_stream(&file);
    doc.save(out_stream,4); //缩进4格
    file.close();
}
void XmlHelper::AddXml(X_Pos* pos,int id,int type)
{
    QFile file("test.xml");
    if(!file.open(QIODevice::ReadOnly|QFile::Text))
            return;

    QDomDocument doc;
    if(!doc.setContent(&file))
    {
        file.close();
        return;
    }

    file.close();
    //get root
    QDomNodeList list=doc.elementsByTagName("route");
    QDomNode node=list.at(type);//get 0 index

    QDomElement name=doc.createElement("name");
    name.setAttribute("id",id);
    QDomElement x_pos=doc.createElement("x_pos");
    QDomText text;
    text=doc.createTextNode(QString::number(pos->x));
    x_pos.appendChild(text);
    name.appendChild(x_pos);

    QDomElement y_pos=doc.createElement("y_pos");
    text=doc.createTextNode(QString::number(pos->y));
    y_pos.appendChild(text);
    name.appendChild(y_pos);

    node.appendChild(name);

    if(!file.open(QFile::WriteOnly|QFile::Truncate))
        return;
    QTextStream out_stream(&file);
    doc.save(out_stream,4); //缩进4格
    file.close();

}
void XmlHelper::Read_Xml(int type)
{
    /*获取所有的节点属性*/
    QFile file("test.xml");
    if(!file.open(QIODevice::ReadOnly|QFile::Text))
            return;
    QDomDocument doc;
    if(!doc.setContent(&file))
    {
        file.close();
        return;
    }
    QDomNodeList list_route=doc.elementsByTagName("route");
    QDomNode node=list_route.at(type);//get 0 index
    //获取所有的节点
    QDomNodeList list= node.childNodes();
    int size=list.count();
    for(int i=0;i<size;i++)
    {
          //XModel
         this->Controller->m=this->Controller->factroy->CreateM();
         QDomElement e=list.at(i).toElement();
         QDomNode n=list.at(i).firstChild();
         QDomNode n1=list.at(i).lastChild();
         Controller->m->id=e.attribute("id").toInt();

         Controller->m->x_pos=n.toElement().text().toInt();
         Controller->m->y_pos=n1.toElement().text().toInt();
         qDebug()<<n.toElement().text().toInt();
         qDebug()<<n1.toElement().text().toInt();
         Controller->m->color=0;
         Controller->m->type=4;
         Controller->m_task.push_back(Controller->m);
         this->Controller->m->Attach(this->Controller->v);
    }
}
void XmlHelper::RemoveXml(int id,int type)
{
    //打开对应的文件
    QFile file("test.xml");
    if(!file.open(QFile::ReadOnly))
        return;
    QDomDocument doc;
    if(!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();
    QDomElement root=doc.documentElement();
    QDomNodeList list_route=doc.elementsByTagName("route");
    QDomNode node=list_route.at(type);//get 0 index
    //获取所有的节点
    QDomNodeList list= node.childNodes(); //由标签名定位
    for(int i=0;i<list.count();i++)
    {
        QDomElement e=list.at(i).toElement();
        qDebug()<<e.attribute("id");
        if(e.attribute("id").toInt()==id)
        {
             node.removeChild(list.at(i));
             break;
        }
    }
    if(!file.open(QFile::WriteOnly|QFile::Truncate))
        return;
    QTextStream out_stream(&file);
    doc.save(out_stream,4); //缩进4格
    file.close();

}
void XmlHelper::UpdateXml(X_Pos* pos,int id,int type)
{
    QFile file("test.xml"); //相对路径、绝对路径、资源路径都可以
    if(!file.open(QFile::ReadOnly))
        return;
    QDomDocument doc;
    if(!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();

    QDomNodeList list_route=doc.elementsByTagName("route");
    QDomNode node_a=list_route.at(type);//get 0 index

    QDomNodeList list=node_a.childNodes();
    //遍历进行数据元素update
    QDomNode node=list.at(id-1).firstChild();
    QDomNode node1=list.at(id-1).lastChild();

    QDomNode oldnode=node.firstChild();
    QDomNode oldnode1=node1.firstChild();

    node.firstChild().setNodeValue(QString::number(pos->x));
    node1.firstChild().setNodeValue(QString::number(pos->y));

    QDomNode newnode=node.firstChild();
    node.replaceChild(newnode,oldnode);
    newnode=node1.firstChild();
    node.replaceChild(newnode,oldnode1);

    if(!file.open(QFile::WriteOnly|QFile::Truncate))
            return;
    QTextStream out_stream(&file);
    doc.save(out_stream,4);
    file.close();
}

XmlHelper::XmlHelper()
{

}
