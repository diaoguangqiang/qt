#ifndef WATER_WIDGET_H
#define WATER_WIDGET_H

#include "qcustomplot.h"

#include <QWidget>
#include <QSplitter>
#include <QLabel>
#include <QPushButton>
#include <QToolButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QEvent>
#include <QPen>
#include <QProgressBar>
#include <QPainter>
//#include <QtWebEngineWidgets/QWebEngineView>

class WaterWidget : public QWidget
{
	Q_OBJECT

public:
	explicit WaterWidget(QWidget *parent = 0);
	~WaterWidget();

	void translateLanguage();

	void showWebEngineView();
	void hideWebEngineView();

private:
	void initRightTop();
	void initRightCenter();
	void initRightCenterFunction();
	void initRightBottom();
	void initLeft();

	void initRight();

	void setupPlot();

protected:

	bool eventFilter(QObject *obj, QEvent *event);

signals:

	void showLoginDialog();
	void showRegisterDialog();

private:
	QSplitter *main_splitter;

	QWidget *left_widget;
	//QWebEngineView *webEngineView;  // 加载比较卡，故去除
	QCustomPlot *plot_; // 画板
	//QLabel *label;
	//QLabel *suggest_label;
	QLabel *system_safe_label;
	//QPushButton *power_button; //立即体检按钮

	QSplitter *right_splitter;
	QWidget *right_widget;
	QWidget *right_top_widget;

	QPushButton *login_button; //登录我的360帐号
	QLabel *priv_label; //皇砖图标
	QLabel *info_label; //开启炫动卫视图标
	QLabel *privilege_label; //转享特权
	QPushButton *register_button; //10秒免费注册
	QPushButton *safe_button; //特权领360炫动logo
	QPushButton *tab_button;  //领取炫动导航功能图标
	QPushButton *pet_button;  //宠物安仔精灵
	QPushButton *lottery_button;  //按在抱枕大派送
	QPushButton *cloud_five_button;  //5G云盘
	QPushButton *caipiao_button;  //彩票

	QWidget *right_center_widget;
	QToolButton *fireproof_button; //360防火墙
	QToolButton *triggerman_button; //360保镖
	QToolButton *net_shop_button; //网购先赔
	QLabel *line_label_1; //虚线
	QLabel *line_label_2; //虚线

	QWidget *right_center_function_widget;
	QLabel *function_label; //功能大全
	QPushButton *more_button; //更多
	QList<QToolButton *> button_list;  //按钮容器

	QWidget *right_bottom_widget;
	QLabel *icon_label; //云图标
	QLabel *connect_label; //成功连接云安全
	QLabel *version_label; //版本号
	QPushButton *version_button; //版本升级
};

#endif // WATER_WIDGET_H
