#ifndef BUILD_H
#define BUILD_H
class Node_Content;
class Builder {
public:
    virtual void builderData(Node_Content* content)=0;
protected:
    Builder(){}
};
#endif // BUILD_H
