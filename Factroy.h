#ifndef FACTROY_H
#define FACTROY_H
#include <iostream>
#include <string>
#include <QDebug>
using namespace std;
class ExportFileApi {
public:
    virtual bool exportData(string data) = 0;
protected:
    ExportFileApi(){}
};
class ExportXmlFile:public ExportFileApi
{
public:
    bool exportData(string data)
    {
       qDebug()<<"正在导出数据到.xml文件"<<endl;
    }
};
class ExportTxtFile : public ExportFileApi {
public:
    bool exportData(string data) {
        qDebug() << "正在导出数据到csv文件" << endl;
        return true;
    }
};

//生成数据到数据库
class ExportDB :public ExportFileApi {
public:
    bool exportData(string data) {
        qDebug() << "正在导出数据到数据库" << endl;
        return true;
    }
};

//实现一个ExportOperate,这个叫导出数据的业务功能对象
class ExportOperate {//他也是接口
public:
    bool exportData(string data) {
        ExportFileApi* pApi = factoryMethod();
        return pApi->exportData(data);
    }
protected:
    virtual ExportFileApi* factoryMethod() = 0;
};

//具体的实现对象，完成导出工作
class ExportTxtFileOperate : public ExportOperate {
protected:
    ExportFileApi* factoryMethod() {
        return new ExportTxtFile();
    }
};

class ExportDBOperate :public ExportOperate {
protected:
    ExportFileApi* factoryMethod() {
        return new ExportDB;
    }
};
class ExportXmlOperate:public ExportOperate
{
protected:
    ExportFileApi* factoryMethod() {
        return new ExportXmlFile;
    }
};

#endif // FACTROY_H
