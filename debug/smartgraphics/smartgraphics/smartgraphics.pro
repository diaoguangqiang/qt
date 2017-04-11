#-------------------------------------------------
#
# Project created by QtCreator 2017-04-09T23:31:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = smartgraphics
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    cmodel.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    cmodel.h

FORMS    += mainwindow.ui
