#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    
private:
    //QNetworkAccessManager * m_manager_;

private slots:
    //void replyFinished( QNetworkReply * );

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
