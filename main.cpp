#include "XimageEdit.h"
#include <QApplication>
#include "Factroy.h"
#include "abstract_factroy.h"
#include"QDebug"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    XimageEdit w;
    w.show();

    return a.exec();
}
