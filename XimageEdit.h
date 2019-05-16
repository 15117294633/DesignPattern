#ifndef XIMAGEEDIT_H
#define XIMAGEEDIT_H

#include <QWidget>

namespace Ui {
class XimageEdit;
}

class XimageEdit : public QWidget
{
    Q_OBJECT

public:
    explicit XimageEdit(QWidget *parent = 0);
    ~XimageEdit();

private:
    Ui::XimageEdit *ui;
};

#endif // XIMAGEEDIT_H
