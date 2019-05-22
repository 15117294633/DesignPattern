#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QToolBar>
#include <QScrollArea>
#include <QPushButton>
#include <QLabel>
#include <QAction>
class  IController;
namespace Ui {
class MainWindow;
}
class Ximage;
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    bool initToolBar();
    bool initEditToolItem(QToolBar* tb);
    bool makeAction(QAction*& action, QWidget* parent, QString text, int key);
    bool makeAction(QAction*& action, QWidget* parent, QString tip, QString icon);
public:

    explicit MainWindow(QWidget *parent = 0);
    QToolBar* ToolBar;
    ~MainWindow();


private:
    QScrollArea* img;
    QPushButton* Btn_Open;
    QLabel* label;
    Ximage* img_s;

    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
