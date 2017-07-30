#ifndef KILLMUMMYWIDGET_H
#define KILLMUMMYWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QToolButton>
#include <QHBoxLayout>

class KillMummyWidget : public QWidget
{
    Q_OBJECT
public:

	explicit KillMummyWidget(QWidget *parent = 0);
	~KillMummyWidget();
	void translateLanguage();

private:

	QLabel *tip_icon_label;  //提示图标
	QLabel *tip_info_label;  //提示信息
	QLabel *tip_suggest_label;  //建议信息
	QToolButton *fast_scan_button; //快速扫描
	QToolButton *full_scan_button; //全盘扫描
	QToolButton *custom_scan_button; //自定义扫描
};

#endif // KILLMUMMYWIDGET_H
