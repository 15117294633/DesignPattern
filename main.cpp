#include "XimageEdit.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    XimageEdit w;
    w.show();

    return a.exec();
}
