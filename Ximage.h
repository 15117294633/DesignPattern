#ifndef XIMAGE_H
#define XIMAGE_H

#include <QWidget>
#include <QImage>
class IController;
class Ximage : public QWidget
{
    Q_OBJECT
public:

    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent*e);

    explicit Ximage(QWidget *parent = nullptr);
protected:
    IController *c = 0;
signals:

public slots:
    void open_slot();
    void erase_slot();
    void pen_slot();
    void rect_slot();
    void circle_slot();
};

#endif // XIMAGE_H
