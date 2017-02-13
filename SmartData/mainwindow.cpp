#include "mainwindow.h"
//#include "ui_mainwindow.h"

#include <QMouseEvent>
#include <QPainter>
//#include <stdlib.h>
#include <qmath.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
    //,ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    //窗口大小
    setMinimumSize(910, 610);
    setMaximumSize(910, 610);
    //去除标题栏
    setWindowFlags(Qt::FramelessWindowHint);
    //使窗体透明
    setAttribute( Qt::WA_TranslucentBackground, true );
    //窗口图标的设置
    setWindowIcon(QIcon(":/image/360logo.ico"));

    m_MousePressed=false;

    //堆栈窗体
    m_stackwid=new QStackedWidget(this);
    m_csxfwid= new csxfwidget(m_stackwid);
    m_dnqlwid=new dnqlWidget(m_stackwid);
    m_yhjswid=new yhjsWidget(m_stackwid);

}



/**
 * @brief MainWindow::slot_iconIsActived
 *          托盘菜单
 * @param reason
 */
void MainWindow::slot_iconIsActived(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
        //点击托盘显示窗口
        case QSystemTrayIcon::Context:
        {
            traymenu->setGeometry(QCursor::pos().rx()-traymenu->width(),QCursor::pos().ry()-traymenu->height(),traymenu->width(),traymenu->height());//托盘菜单的位置
            break;
        }

        case QSystemTrayIcon::Trigger:
        case QSystemTrayIcon::DoubleClick:
        {
            showNormal();
            activateWindow();
            break;
        }

        default:
            break;
    }
}

/**
 * @brief MainWindow::slot_hideanimationfinished
 */
void MainWindow::slot_hideanimationfinished()
{
    maskmainwid->hide();
}

MainWindow::~MainWindow()
{
    //delete ui;

    delete m_masklowwincloseani;
    delete m_maskupwincloseani;
    delete m_maskupwinshowani;
    delete m_masklowwinshowani;
    delete system_tray;//定要消除对象
}

/**
 * @brief MainWindow::slot_hideanimation
 *  隐藏两个界面的动画
 */
void MainWindow::slot_hideanimation()
{
    m_masklowwincloseani->start();
    m_maskupwincloseani->start();
}

/**
 * @brief MainWindow::returnanimation
 */
void MainWindow::returnanimation()
{
    maskmainwid->show();
    m_maskupwinshowani->start();
    m_masklowwinshowani->start();
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
    QRect *rc=new QRect(5,5,900,150);

    //如果按下的位置
    if(rc->contains(this->mapFromGlobal(QCursor::pos()))==true)
    {
        if (event->button() == Qt::LeftButton)
        {
            m_WindowPos = this->pos();
            m_MousePos = event->globalPos();
            this->m_MousePressed = true;
        }
    }
}

/**
 * @brief MainWindow::mouseMoveEvent
 * @param event
 */
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (m_MousePressed)
    {
        this->move(m_WindowPos + (event->globalPos() - m_MousePos));
    }
}

/**
 * @brief MainWindow::mouseReleaseEvent
 * @param event
 */
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        this->m_MousePressed = false;
    }
}



/**
 * @brief MainWindow::paintEvent
 */
void MainWindow::paintEvent(QPaintEvent*)
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(9, 9, this->width()-18, this->height()-18);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QBrush(Qt::white));

    QColor color(0, 0, 0, 50);
    for(int i=0; i<9; i++)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRect(9-i, 9-i, this->width()-(9-i)*2, this->height()-(9-i)*2);
        color.setAlpha(150 - qSqrt(i)*50);

        painter.setPen(color);
        painter.drawPath(path);
    }
}

