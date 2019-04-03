#ifndef IGRAPH_H
#define IGRAPH_H
class QPainter;
class QImage;
class XModel;
class IGraph
{
public:
    virtual void Init(QPainter* p,QImage* img)
    {
        this->img=img;
        this->painter=p;
    }
    virtual void  Draw(XModel *m) = 0;
protected:
    QPainter* painter;
    QImage* img;
};

#endif // IGRAPH_H
