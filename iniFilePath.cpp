#include "iniFilePath.h"
#include "QString"
#include "QSettings"
iniFilePath::iniFilePath()
{

}
void iniFilePath::Read_from_Ini(int& num)
{
   QString iniFilePath ="MyINI.ini";//定义为宏
   QSettings settings(iniFilePath,QSettings::IniFormat);
   num = settings.value("Group1/Count").toInt();
}
unsigned int iniFilePath::Read_RouteNum(int i)
{
    QString iniFilePath ="MyINI.ini";
    QSettings settings(iniFilePath,QSettings::IniFormat);
    QString val=QString("Group2/Val%1").arg(i);

    return settings.value(val).toInt();
}
void iniFilePath::Write_to_Ini(int num)
{
    QString iniFilePath ="MyINI.ini";
    QSettings settings(iniFilePath,QSettings::IniFormat);
    settings.setValue("Group1/Count",num);
}
void iniFilePath::Write_RouteNum(unsigned int num,int i)
{
    QString iniFilePath ="MyINI.ini";
    QSettings settings(iniFilePath,QSettings::IniFormat);
    QString val=QString("Group2/Val%1").arg(i);
    settings.setValue(val,num);
}

