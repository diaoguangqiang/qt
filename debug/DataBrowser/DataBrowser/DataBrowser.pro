#-------------------------------------------------
#
# Project created by QtCreator 2017-02-13T11:26:21
#
#-------------------------------------------------

QT       += core gui webkitwidgets webkit

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DataBrowser
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    toolbar.qrc \
    html.qrc

OTHER_FILES += \
    js/bas.js \
    html/bas.html \
    svg/bas.svg \
    html/index.html \
    html/menu.html \
    html/Z01_BAS_SHUIXITONG.html
