#ifndef INIT_PARAM_H
#define INIT_PARAM_H

class Init_Param
{

public:
    static Init_Param* Get_Obj()
    {
        static  Init_Param obj;
        return &obj;
    }
    void Load_Param();
    void Creat_Folder();
    void Creat_File();
    Init_Param();
};

#endif // INIT_PARAM_H
