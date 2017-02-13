#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //固定窗口大小
    //setFixedSize(950, 600);

    //本地文件
    QString urlName("qrc:/html/index.html");
    //QUrl url = QUrl::fromUserInput(urlName);

    QString strMapPath="file:///";
    strMapPath+=QCoreApplication::applicationDirPath();
    QString htmlName = "/html/index.html";
    strMapPath += htmlName;

    //printf("out: %s\n", strMapPath.toStdString().c_str());
    qDebug("%s\n", strMapPath.toStdString().c_str());

    //strMapPath+="./index.html";
    QUrl url(strMapPath);

    //显示主页
    ui->webView->load(url);
    ui->webView->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}
