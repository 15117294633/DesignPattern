#include "Init_Param.h"
#include "QDir"
#include "QFile"
Init_Param::Init_Param()
{

}
void Init_Param::Load_Param()
{
    Creat_File();
    Creat_Folder();
}
void Init_Param::Creat_Folder()
{
    QDir dir;
    if(!dir.exists("route"))
    {
        dir.mkdir("route");
    }
    else    //加载文件至对应的文件中
    {


    }

}
void Init_Param::Creat_File()
{
     QFile file("MyINI.ini");
     if(!file.exists())
     {
         file.open( QIODevice::WriteOnly|QIODevice::Text);
         file.close();
     }
      QFile file1("test.xml");
      if(!file1.exists())
      {
          file1.open( QIODevice::WriteOnly|QIODevice::Text);
          file1.close();
      }

}
