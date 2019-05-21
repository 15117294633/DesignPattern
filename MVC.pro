#-------------------------------------------------
#
# Project created by QtCreator 2019-03-21T15:16:06
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MVC
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        XimageEdit.cpp \
    Ximage.cpp \
    XEditView.cpp \
    XSubject.cpp \
    XModel.cpp \
    IController.cpp \
    XControllerFactory.cpp \
    XPenGraph.cpp \
    XErasGraph.cpp \
    XRectGraph.cpp \
    XImageGraph.cpp \
    XCircleGraph.cpp \
    MainWindow.cpp \
    NodeDialog.cpp \
    TxtBuild.cpp \
    RouteMange.cpp \
    Route_Oper.cpp \
    Do_move.cpp \
    DoAddRoute.cpp \
    DoRemoveRoute.cpp \
    SqlLite_Helper.cpp \
    XmlHelper.cpp

HEADERS += \
        XimageEdit.h \
    Ximage.h \
    XEditView.h \
    XSubject.h \
    IObserver.h \
    XModel.h \
    IController.h \
    IControllerFactroy.h \
    IView.h \
    XControllerFactory.h \
    IGraph.h \
    XPenGraph.h \
    XErasGraph.h \
    Factroy.h \
    build.h \
    XRectGraph.h \
    XErasGraph.h \
    XImageGraph.h \
    XCircleGraph.h \
    MainWindow.h \
    NodeDialog.h \
    TxtBuild.h \
    RouteMange.h \
    Route_Oper.h \
    IOperator.h \
    Do_move.h \
    DoAddRoute.h \
    DoRemoveRoute.h \
    SqlLite_Helper.h \
    MySql.h \
    XmlHelper.h

FORMS += \
    MainWindow.ui

RESOURCES += \
    res.qrc
