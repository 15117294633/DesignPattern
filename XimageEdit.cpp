#include "XimageEdit.h"
#include "ui_ximageedit.h"
XimageEdit::XimageEdit(QWidget *parent) :
    QWidget(parent),
   ui(new Ui::XimageEdit)
{
    ui->setupUi(this);
    connect(ui->openfile,SIGNAL(clicked(bool)),ui->image,SLOT(open_slot(void)));
    connect(ui->Draw_Pen,SIGNAL(clicked(bool)),ui->image,SLOT(pen_slot(void)));
    connect(ui->Erase,SIGNAL(clicked(bool)),ui->image,SLOT(erase_slot(void)));
    connect(ui->rect,SIGNAL(clicked(bool)),ui->image,SLOT(rect_slot(void)));
    connect(ui->Circle,SIGNAL(clicked(bool)),ui->image,SLOT(circle_slot(void)));
}
XimageEdit::~XimageEdit()
{
    delete ui;
}
