#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::eventFilter
 * @param obj
 * @param event
 * @return
 */
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    //反回到上一级 即重复使用
    return QObject::eventFilter(obj,event);
}

/**
 * @brief MainWindow::mousePressEvent
 * @param event
 */
void MainWindow::mousePressEvent(QMouseEvent *event)
{

}

/**
 * @brief MainWindow::mouseReleaseEvent
 * @param event
 */
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{

}

/**
 * @brief MainWindow::mouseMoveEvent
 * @param event
 */
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{

}

/**
 * @brief MainWindow::paintEvent
 */
void MainWindow::paintEvent(QPaintEvent*)
{

}

