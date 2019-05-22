#include "iniFilePath.h"
#include "QString"
#include "QSettings"
iniFilePath::iniFilePath()
{

}
void iniFilePath::Read_from_Ini(int& num)
{
   QString iniFilePath ="MyINI.ini";
   QSettings settings(iniFilePath,QSettings::IniFormat);
   num = settings.value("Group1/Count").toInt();
}
void iniFilePath::Write_to_Ini(int num)
{
    QString iniFilePath ="MyINI.ini";
    QSettings settings(iniFilePath,QSettings::IniFormat);
    settings.setValue("Group1/Count",num);
}
