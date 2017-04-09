#include "mainwindow.h"
#include <QApplication>

#include <QtWebKitWidgets/QWebView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    //QWebView v;
   // v.load(QUrl("https://www.baidu.com"));
   // v.show();


    return a.exec();
}
