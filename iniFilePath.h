#ifndef INIFILEPATH_H
#define INIFILEPATH_H

class iniFilePath
{
public:
    static iniFilePath* Get_Obj()
    {
        static  iniFilePath obj;
        return &obj;
    }
    iniFilePath();
    void Read_from_Ini(int& num);
    unsigned int Read_RouteNum(int i);
    void Write_to_Ini(int num);
    void Write_RouteNum(unsigned int num,int i);

};

#endif // INIFILEPATH_H
