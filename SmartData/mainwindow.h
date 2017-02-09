#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "csxfwidget.h"
#include "dnqlwidget.h"
#include "yhjswidget.h"
#include <QPropertyAnimation>
#include "maskmainwidget.h"
#include <QSystemTrayIcon>
#include "trayiconmenu.h"


//#include <QtNetwork>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
protected:
    bool eventFilter(QObject *, QEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);

    bool    m_MousePressed;
    QPoint  m_MousePos;
    QPoint  m_WindowPos;

private:
    QPropertyAnimation *m_maskupwincloseani;
    QPropertyAnimation *m_masklowwincloseani;
    QPropertyAnimation *m_maskupwinshowani;
    QPropertyAnimation *m_masklowwinshowani;
    trayIconMenu *traymenu;
    QSystemTrayIcon *system_tray;
    //加载最前面的两个widget
    maskmainwidget *maskmainwid;
    QStackedWidget *m_stackwid;
    csxfwidget *m_csxfwid;
    dnqlWidget *m_dnqlwid;
    yhjsWidget *m_yhjswid;

private slots:
    //void replyFinished( QNetworkReply * );

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
