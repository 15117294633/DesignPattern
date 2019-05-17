#ifndef TXTBUILD_H
#define TXTBUILD_H
#include "build.h"
#include "QString"
//拼接称为一个字符串
class TxtBuild:public Builder
{
private:
    QString con;
public:
    QString builderData(Node_Content* content);
    QString ByteArrayToHexString(QByteArray data);
    TxtBuild();
};

#endif // TXTBUILD_H
