#ifndef ACCOUNTITEM_H
#define ACCOUNTITEM_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMouseEvent>

class AccountItem: public QWidget
{
    Q_OBJECT

public:

    explicit AccountItem(QWidget *parent = 0);
    ~AccountItem();
    void setAccountNumber(QString account_text);
    QString getAccountNumber();

protected:

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:

    void showAccount(QString account);
    void removeAccount(QString account_number_text);

private slots:

    void removeAccount();

private:

    QLabel *account_number;  //账号
    QPushButton *delede_button;  //删除账号按钮
    bool mouse_press;

};

#endif // ACCOUNTITEM_H
