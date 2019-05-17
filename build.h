#ifndef BUILD_H
#define BUILD_H
#include "QString"
class Node_Content;
class Builder {
public:
    virtual QString builderData(Node_Content* content)=0;
protected:
    Builder(){}
};
#endif // BUILD_H
