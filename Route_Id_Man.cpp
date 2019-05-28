#include "Route_Id_Man.h"
#include "iniFilePath.h"
#include "QDebug"
Route_Id_Man::Route_Id_Man()
{

}
int Route_Id_Man::__rt_ffs(unsigned long int value)
{
    /* 如果值为 0，则直接返回 0 */
    if (value == 0) return 0;

    /* 检查 bits [07:00]
    这里加 1 的原因是避免当第一个置 1 的位是位 0 时
    返回的索引号与值都为 0 时返回的索引号重复 */
    if (value & 0xff)
    return __lowest_bit_bitmap[value & 0xff] + 1;

    /* 检查 bits [15:08] */
    if (value & 0xff00)
    return __lowest_bit_bitmap[(value & 0xff00) >> 8] + 9;

    /* 检查 bits [23:16] */
    if (value & 0xff0000)
    return __lowest_bit_bitmap[(value & 0xff0000) >> 16] + 17;

    /* 检查 bits [31:24] */
     return __lowest_bit_bitmap[(value & 0xff000000) >> 24] + 25;
}
void Route_Id_Man::Set_Route_Bit(unsigned int val,int i)
{
    route_bit[i]=val;
    iniFilePath::Get_Obj()->Write_RouteNum(route_bit[i],i);
}
void Route_Id_Man::Load_All_Bits()
{
    //后期从配置文件中加载
    for(int i=0;i<8;i++)
    {
       route_bit[i]=iniFilePath::Get_Obj()->Read_RouteNum(i);
    }

}
//1位未被使用 0已经使用了
//32*8=256
int Route_Id_Man::Get_Route_Id()
{
    int ret=0;
    for(int i=0;i<8&&!ret;i++)
    {
        int rett;
        rett=__rt_ffs(route_bit[i]);
        if(rett!=0)
        {
            ret=rett+i*32;
            route_bit[i]&=~(1<<(rett-1));
            iniFilePath::Get_Obj()->Write_RouteNum(route_bit[i],i);
            break;
        }
    }
    return ret;
}
void Route_Id_Man::Clear_Route_Id(int index)
{
    int array_index=index/32;
    int offset=index%32;
    qDebug()<<array_index<<":"<<offset;
    route_bit[array_index]|=(1<<(offset-1));
    iniFilePath::Get_Obj()->Write_RouteNum(route_bit[array_index],array_index);
}

