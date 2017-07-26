#ifndef TITLEWIDGET_H
#define TITLEWIDGET_H

#include "push_button.h"
#include "tool_button.h"

#include <QWidget>
#include <QLabel>
#include <QList>
#include <QPushButton>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSignalMapper>


class TitleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TitleWidget(QWidget *parent = 0);
	void translateLanguage();

signals:

    void showSkin();
    void showMin();
	void showMainMenu();
	void closeWidget();
	void turnPage(int current_page);

public slots:

	void turnPage(QString current_page);

private:

    QPoint press_point;//鼠标按下去的点
    bool is_move;

	QLabel *version_title; //标题
	PushButton *medal_button; //勋章墙
    PushButton *skin_button; //换肤
    PushButton *main_menu_button; //主菜单
    PushButton *min_button; //最小化
    PushButton *feedback_button; //反馈意见
    PushButton *close_button; //关闭

	QLabel *safe_360_label;  //360安全卫士
	QLabel *safe_label;  //360安全卫士

	QList<ToolButton *> button_list;
};

#endif // TITLEWIDGET_H
