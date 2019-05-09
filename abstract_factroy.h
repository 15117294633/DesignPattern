#ifndef ABSTRACT_FACTROY_H
#define ABSTRACT_FACTROY_H
/*no used model*/
class FrameApi
 {

public:
    virtual void draw() = 0;
protected:
    FrameApi() {};
};
class LayoutApi {//分辨率的布局器
public:
    virtual void installFrame() = 0;
protected:
    LayoutApi(){};
};
//
//pc上的Frame
class ComputerFrame :public FrameApi {
public:
    ComputerFrame(int pins) : m_pins(pins) {

    }
    void draw() {
        cout << "pc frame" << m_pins<<endl;
    }
private:
    int m_pins;
};

class MobileFrame :public FrameApi {
public:
    MobileFrame(int pins):m_pins(pins){}
    void draw() {
        cout << "mobile frame" << m_pins<<endl;
    }

private:
    int m_pins;
};
class HighLayout :public LayoutApi {
public:
    HighLayout(int FrameAdpaterPins):m_FrameAdpaterPins(FrameAdpaterPins){}
    void installFrame() {
        cout << "now pc " << m_FrameAdpaterPins << endl;
    }

private:
    int m_FrameAdpaterPins;
};

//低分辨率的布局
class LowLayout :public LayoutApi {
public:
    LowLayout(int FrameAdpaterPins) :m_FrameAdpaterPins(FrameAdpaterPins) {}
    void installFrame() {
        cout << "now mobile" << m_FrameAdpaterPins << endl;
    }

private:
    int m_FrameAdpaterPins;
};
//简单工厂
class Frame_Factroy
{
public:
    static FrameApi* Creat_api(int type)
    {
        FrameApi* frame=nullptr;
        if(type==1)
        {
           frame=new ComputerFrame(1024);
        }
        else if(type==2)
        {
            frame=new MobileFrame(720);
        }
        return frame;
    }
    Frame_Factroy() {}
};


class Layout_Factroy
{
public:
    static LayoutApi* Creat_api(int type)
    {
        LayoutApi* lay=nullptr;
        if(type==1)
        {
           lay=new HighLayout(1024);
        }
        else if(type==2)
        {
            lay=new LowLayout(720);
        }
        return lay;
    }
    Layout_Factroy() {}
};
/*实现*/
class GUIEngineer {
public:
    //FrameType:是用来表述选择Frame控件的类型
//	//LayoutType:是用来表述选择布局管理器的类型
    void prepareDraw(int FrameType, int LayoutType) {
        this->pFrame = Frame_Factroy::Creat_api(FrameType);
        this->pLayout = Layout_Factroy::Creat_api(LayoutType);
        pFrame->draw();
        pLayout->installFrame();
    }
private:
    FrameApi* pFrame;
    LayoutApi* pLayout;
};
/*使用抽象工厂实现code*/
class AbstractFactroy
{
public:
    virtual FrameApi* Creat_Frame()=0;
    virtual LayoutApi* Creat_Lay()=0;
protected:
    AbstractFactroy()
    {

    }
};
class High_Factroy:public AbstractFactroy
{
public:
    FrameApi* Creat_Frame()
    {
        return new ComputerFrame(1024);
    }
    LayoutApi* Creat_Lay()
    {
        return new HighLayout(1024);
    }
};

class Low_Factroy:public AbstractFactroy
{
public:
    FrameApi* Creat_Frame()
    {
        return new MobileFrame(720);
    }
    LayoutApi* Creat_Lay()
    {
        return new LowLayout(720);
    }
};

class GUIFactroyEngineer {
public:
    //FrameType:是用来表述选择Frame控件的类型
//	//LayoutType:是用来表述选择布局管理器的类型
    void prepareDraw(AbstractFactroy* fact) {
        this->pFrame = fact->Creat_Frame();
        this->pLayout = fact->Creat_Lay();
        pFrame->draw();
        pLayout->installFrame();
    }
private:
    FrameApi* pFrame;
    LayoutApi* pLayout;
};
#endif
