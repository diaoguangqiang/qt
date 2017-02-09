#-------------------------------------------------
#
# Project created by QtCreator 2017-01-28T16:29:27
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmartData
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    trayiconmenu.cpp \
    maskmainwidget.cpp \
    abstmainwidget.cpp \
    csxfwidget.cpp \
    dnqlwidget.cpp \
    yhjswidget.cpp

HEADERS  += mainwindow.h \
    trayiconmenu.h \
    maskmainwidget.h \
    abstmainwidget.h \
    csxfwidget.h \
    dnqlwidget.h \
    yhjswidget.h

FORMS    += mainwindow.ui
