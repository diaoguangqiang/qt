#include "water_widget.h"

#include <QCoreApplication>

QReadWriteLock lock_realtime_data_;

WaterWidget::WaterWidget(QWidget *parent)
: QWidget(parent)
{
	// 把空间区域分为左右两部分， 左边区域面积最大，右边区域站1/3
	main_splitter = new QSplitter();
	main_splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	main_splitter->setOrientation(Qt::Horizontal);
	main_splitter->setHandleWidth(1);
	main_splitter->setStyleSheet("QSplitter::handle{background-color:red}");

	this->initLeft();
	this->initRight();
	this->initRightTop();
	this->initRightCenter();
	this->initRightCenterFunction();
	this->initRightBottom();

	right_splitter->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	right_splitter->setOrientation(Qt::Vertical);
	right_splitter->setHandleWidth(1);

	right_top_widget->setFixedSize(250, 130);
	right_center_widget->setFixedSize(250, 90);
	right_bottom_widget->setFixedSize(250, 30);
	right_splitter->addWidget(right_top_widget);
	right_splitter->addWidget(right_center_widget);
	right_splitter->addWidget(right_center_function_widget);
	right_splitter->addWidget(right_bottom_widget);

	main_splitter->addWidget(left_widget);
	main_splitter->addWidget(right_splitter);
	
	// 
	//paintWeekHistoryWater();
	paintRealTimeWater();

	initThread();

	//禁止拖动
	for (int i = 0; i < right_splitter->count(); i++)
	{
		QSplitterHandle *handle = right_splitter->handle(i);
		handle->setEnabled(false);
	}

	for (int i = 0; i < main_splitter->count(); i++)
	{
		QSplitterHandle *handle = main_splitter->handle(i);
		handle->setEnabled(false);
	}

	QHBoxLayout *main_layout = new QHBoxLayout();
	main_layout->addWidget(main_splitter);
	main_layout->setSpacing(0);
	main_layout->setContentsMargins(0, 0, 0, 0);

	this->setLayout(main_layout);
	this->translateLanguage();
}

WaterWidget::~WaterWidget()
{
	thread_reader_->stop(true);
}

void WaterWidget::initThread()
{
	thread_reader_ = new ReadRedisThread("127.0.0.1", 6379, &map_realtime_data_, this);
}

void WaterWidget::initLeft()
{
	left_widget = new QWidget();
	//label = new QLabel();
	//webEngineView = new QWebEngineView();
	plot_ = new QCustomPlot(this);
	//suggest_label = new QLabel();
	system_safe_label = new QLabel();
	//power_button = new QPushButton();

	left_widget->resize(650, 500);

	/*
	QPixmap label_pixmap(":/contentWidget/computer");
	label->setPixmap(label_pixmap);
	label->setFixedSize(label_pixmap.size());
	*/

	//webEngineView->setObjectName(QStringLiteral("webEngineView"));
	//webEngineView->setGeometry(QRect(10, 10, 831, 361));
	//webEngineView->setUrl(QUrl(QStringLiteral("about:blank")));
	//webEngineView->load(QUrl("file:///" + qApp->applicationDirPath() + "/html/gauge.html"));
	//webEngineView->load(QUrl("file:///" + QCoreApplication::applicationDirPath() + "/html/gauge.html"));
	//webEngineView->load(QUrl(QString("http://www.baidu.com/")));
	//webEngineView->show();
	//webEngineView->hide();

	
	plot_->setObjectName(QStringLiteral("plot"));
	QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
	//设置水平大小策略的缩放因子 [0, 255]
	sizePolicy.setHorizontalStretch(1);
	sizePolicy.setVerticalStretch(1);
	sizePolicy.setHeightForWidth(plot_->sizePolicy().hasHeightForWidth());
	plot_->setSizePolicy(sizePolicy);
	

	/*QFont suggest_font = suggest_label->font();
	suggest_font.setPointSize(12);
	suggest_font.setBold(true);
	suggest_label->setFont(suggest_font);
	suggest_label->setObjectName("grayLabel");
	*/
	
	QFont system_safe_font = system_safe_label->font();
	system_safe_font.setBold(true);
	system_safe_label->setFont(system_safe_font);
	system_safe_label->setObjectName("grayLabel");
	//system_safe_label->cent
	

	/*QPixmap pixmap(":/contentWidget/power");
	power_button->setIcon(pixmap);
	power_button->setIconSize(pixmap.size());
	power_button->setFixedSize(180, 70);
	power_button->setObjectName("greenButton");
	*/

	/*QFont power_font = power_button->font();
	power_font.setPointSize(16);
	power_button->setFont(power_font);
	*/

	/*
	QVBoxLayout *v_layout = new QVBoxLayout();
	//v_layout->addWidget(suggest_label);
	v_layout->addWidget(system_safe_label);
	v_layout->addWidget(webEngineView);
	v_layout->addStretch();
	v_layout->setSpacing(10);
	v_layout->setContentsMargins(0, 20, 0, 0);

	QHBoxLayout *h_layout = new QHBoxLayout();
	//h_layout->addWidget(label, 0, Qt::AlignTop);
	h_layout->addWidget(webEngineView, 0, Qt::AlignTop);
	h_layout->addLayout(v_layout);
	h_layout->addStretch();
	h_layout->setSpacing(20);
	h_layout->setContentsMargins(30, 20, 0, 0);
	*/

	QVBoxLayout *main_layout = new QVBoxLayout();
	//main_layout->setMargin(5); // 上下边距
	//main_layout->setSpacing(2); // 控件之间边距
	//main_layout->addLayout(h_layout);
	//main_layout->addWidget(power_button, 0, Qt::AlignCenter);
	main_layout->addWidget(system_safe_label, 0, Qt::AlignCenter| Qt::AlignHCenter);
	//main_layout->addWidget(webEngineView);
	main_layout->addWidget(plot_);
	
	main_layout->addStretch();
	main_layout->setSpacing(10);
	main_layout->setContentsMargins(10, 20, 20, 20);

	left_widget->setLayout(main_layout);
}

void WaterWidget::initRight()
{
	right_splitter = new QSplitter();
}

void WaterWidget::initRightTop()
{
	right_top_widget = new QWidget();
	login_button = new QPushButton();
	priv_label = new QLabel();
	info_label = new QLabel();
	privilege_label = new QLabel();
	register_button = new QPushButton();
	safe_button = new QPushButton();
	tab_button = new QPushButton();
	pet_button = new QPushButton();
	lottery_button = new QPushButton();
	cloud_five_button = new QPushButton();
	caipiao_button = new QPushButton();

	login_button->setFixedSize(240, 60);
	login_button->setObjectName("loginButton");
	QFont login_font = login_button->font();
	login_font.setBold(true);
	login_font.setPointSize(12);
	login_button->setFont(login_font);

	priv_label->setPixmap(QPixmap(":/contentWidget/priv"));
	QPixmap safe_pixmap(":/contentWidget/360");
	safe_button->setIcon(safe_pixmap);
	safe_button->setFixedSize(safe_pixmap.size());
	QPixmap tab_pixmap(":/contentWidget/tab");
	tab_button->setIcon(tab_pixmap);
	tab_button->setFixedSize(tab_pixmap.size());
	QPixmap pet_pixmap(":/contentWidget/pet");
	pet_button->setIcon(pet_pixmap);
	pet_button->setFixedSize(tab_pixmap.size());
	QPixmap lottery_pixmap(":/contentWidget/lottery");
	lottery_button->setIcon(lottery_pixmap);
	lottery_button->setFixedSize(lottery_pixmap.size());
	QPixmap cloud_five_pixmap(":/contentWidget/cloud_five");
	cloud_five_button->setIcon(cloud_five_pixmap);
	cloud_five_button->setFixedSize(cloud_five_pixmap.size());
	QPixmap caipiao_pixmap(":/contentWidget/caipiao");
	caipiao_button->setIcon(caipiao_pixmap);
	caipiao_button->setFixedSize(caipiao_pixmap.size());

	register_button->setCursor(Qt::PointingHandCursor);
	safe_button->setCursor(Qt::PointingHandCursor);
	tab_button->setCursor(Qt::PointingHandCursor);
	pet_button->setCursor(Qt::PointingHandCursor);
	lottery_button->setCursor(Qt::PointingHandCursor);
	cloud_five_button->setCursor(Qt::PointingHandCursor);
	caipiao_button->setCursor(Qt::PointingHandCursor);

	register_button->setObjectName("blueButton");
	safe_button->setObjectName("transparentButton");
	tab_button->setObjectName("transparentButton");
	pet_button->setObjectName("transparentButton");
	lottery_button->setObjectName("transparentButton");
	cloud_five_button->setObjectName("transparentButton");
	caipiao_button->setObjectName("transparentButton");

	QHBoxLayout *login_layout = new QHBoxLayout();
	login_layout->addWidget(login_button);
	login_layout->addStretch();
	login_layout->setContentsMargins(15, 0, 0, 0);

	QHBoxLayout *register_layout = new QHBoxLayout();
	register_layout->addStretch();
	register_layout->addWidget(priv_label);
	register_layout->addWidget(info_label);
	register_layout->addWidget(register_button);
	register_layout->addStretch();
	register_layout->setSpacing(5);
	register_layout->setContentsMargins(0, 0, 0, 0);

	QHBoxLayout *privilege_layout = new QHBoxLayout();
	privilege_layout->addStretch();
	privilege_layout->addWidget(privilege_label);
	privilege_layout->addWidget(safe_button);
	privilege_layout->addWidget(tab_button);
	privilege_layout->addWidget(pet_button);
	privilege_layout->addWidget(lottery_button);
	privilege_layout->addWidget(cloud_five_button);
	privilege_layout->addWidget(caipiao_button);
	privilege_layout->addStretch();
	privilege_layout->setSpacing(8);
	privilege_layout->setContentsMargins(0, 0, 0, 0);

	QVBoxLayout *main_layout = new QVBoxLayout();
	main_layout->addStretch();
	main_layout->addLayout(login_layout);
	main_layout->addLayout(register_layout);
	main_layout->addLayout(privilege_layout);
	main_layout->addStretch();
	main_layout->setSpacing(5);
	main_layout->setContentsMargins(10, 10, 10, 10);

	connect(login_button, SIGNAL(clicked()), this, SIGNAL(showLoginDialog()));
	connect(register_button, SIGNAL(clicked()), this, SIGNAL(showRegisterDialog()));

	right_top_widget->setLayout(main_layout);
}

void WaterWidget::initRightCenter()
{
	right_center_widget = new QWidget();
	fireproof_button = new QToolButton();
	triggerman_button = new QToolButton();
	net_shop_button = new QToolButton();
	line_label_1 = new QLabel();
	line_label_2 = new QLabel();
	line_label_1->setFixedWidth(10);
	line_label_2->setFixedWidth(10);
	line_label_1->installEventFilter(this);
	line_label_2->installEventFilter(this);

	fireproof_button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	triggerman_button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	net_shop_button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

	QPixmap fireproof_pixmap(":/contentWidget/fireproof");
	fireproof_button->setIcon(fireproof_pixmap);
	fireproof_button->setIconSize(fireproof_pixmap.size());
	fireproof_button->setFixedSize(fireproof_pixmap.width() + 25, fireproof_pixmap.height() + 25);

	QPixmap triggerman_pixmap(":/contentWidget/triggerman");
	triggerman_button->setIcon(triggerman_pixmap);
	triggerman_button->setIconSize(triggerman_pixmap.size());
	triggerman_button->setFixedSize(triggerman_pixmap.width() + 25, triggerman_pixmap.height() + 25);

	QPixmap net_shop_pixmap(":/contentWidget/net_shop");
	net_shop_button->setIcon(net_shop_pixmap);
	net_shop_button->setIconSize(net_shop_pixmap.size());
	net_shop_button->setFixedSize(net_shop_pixmap.width() + 25, net_shop_pixmap.height() + 25);

	fireproof_button->setObjectName("transparentToolButton");
	triggerman_button->setObjectName("transparentToolButton");
	net_shop_button->setObjectName("transparentToolButton");

	QHBoxLayout *h_layout = new QHBoxLayout();
	h_layout->addWidget(fireproof_button);
	h_layout->addWidget(line_label_1);
	h_layout->addWidget(triggerman_button);
	h_layout->addWidget(line_label_2);
	h_layout->addWidget(net_shop_button);
	h_layout->setSpacing(0);
	h_layout->setContentsMargins(0, 0, 0, 0);

	right_center_widget->setLayout(h_layout);
}

void WaterWidget::initRightCenterFunction()
{
	right_center_function_widget = new QWidget();
	function_label = new QLabel();
	more_button = new QPushButton();

	QFont function_font = function_label->font();
	function_font.setBold(true);
	function_label->setFont(function_font);
	function_label->setObjectName("infoLabel");
	more_button->setFixedSize(50, 25);
	more_button->setObjectName("blueButton");
	more_button->setCursor(Qt::PointingHandCursor);

	QHBoxLayout *h_layout = new QHBoxLayout();
	h_layout->addWidget(function_label);
	h_layout->addStretch();
	h_layout->addWidget(more_button);
	h_layout->setSpacing(0);
	h_layout->setContentsMargins(10, 5, 0, 0);

	QStringList string_list;
	string_list << ":/contentWidget/recovery" << ":/contentWidget/mobile" << ":/contentWidget/game_box" << ":/contentWidget/desktop"
		<< ":/contentWidget/net_repair" << ":/contentWidget/auto_run" << ":/contentWidget/net_speed" << ":/contentWidget/net_pretext"
		<< ":/contentWidget/first_add";

	QGridLayout *grid_layout = new QGridLayout();
	for (int i = 0; i < string_list.size(); i++)
	{
		QToolButton *tool_button = new QToolButton();
		tool_button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
		QPixmap button_pixmap(string_list.at(i));
		tool_button->setIcon(button_pixmap);
		tool_button->setIconSize(button_pixmap.size());
		tool_button->setFixedSize(button_pixmap.width() + 50, button_pixmap.height() + 35);
		tool_button->setObjectName("functionButton");

		button_list.append(tool_button);
		grid_layout->addWidget(tool_button, i / 3, i % 3);
	}
	grid_layout->setSpacing(0);
	grid_layout->setContentsMargins(5, 0, 5, 5);

	QVBoxLayout *v_layout = new QVBoxLayout();
	v_layout->addLayout(h_layout);
	v_layout->addLayout(grid_layout);
	v_layout->addStretch();
	v_layout->setSpacing(10);
	v_layout->setContentsMargins(0, 0, 0, 0);

	right_center_function_widget->setLayout(v_layout);
}

void WaterWidget::initRightBottom()
{
	right_bottom_widget = new QWidget();
	icon_label = new QLabel();
	connect_label = new QLabel();
	version_label = new QLabel();
	version_button = new QPushButton();

	QPixmap label_pixmap(":/contentWidget/cloud");
	icon_label->setPixmap(label_pixmap);
	icon_label->setFixedSize(label_pixmap.size());

	QPixmap pixmap(":/contentWidget/version");
	version_button->setIcon(pixmap);
	version_button->setIconSize(pixmap.size());
	version_button->setFixedSize(20, 20);
	version_button->setObjectName("transparentButton");

	QHBoxLayout *bottom_layout = new QHBoxLayout();
	bottom_layout->addWidget(icon_label);
	bottom_layout->addWidget(connect_label);
	bottom_layout->addStretch();
	bottom_layout->addWidget(version_label);
	bottom_layout->addWidget(version_button);
	bottom_layout->setSpacing(5);
	bottom_layout->setContentsMargins(10, 0, 10, 0);
	right_bottom_widget->setLayout(bottom_layout);
}

void WaterWidget::paintWeekHistoryWater()
{
	// The following plot setup is taken from the sine demo:
	// add two new graphs and set their look:
	plot_->addGraph();
	plot_->graph(0)->setPen(QPen(Qt::red)); // line color blue for first graph
	// 填充
	//plot_->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue

	plot_->addGraph();
	plot_->graph(1)->setPen(QPen(Qt::green)); // line color red for second graph
	// generate some points of data (y0 for first, y1 for second graph):
	QVector<double> x(7), y(7)/*, y1(250)*/;
	QVector<double> x_low(7), y_low(7);

	for (int i = 0; i < x.size(); ++i)
	{
		//x[i] = i / (double)(x.size() - 1) * 10;
		//y[i] = qCos(x[i] * 0.8 + qSin(x[i] * 0.16 + 1.0))*qSin(x[i] * 0.54) + 1.4;
		x[i] = x_low[i] = i + 1;
		//y[i] = 30 + i;
	}

	y[0] = 35; y[1] = 33; y[2] = 32; y[3] = 36;	y[4] = 33; y[5] = 35; y[6] = 38;
	y_low[0] = 24; y_low[1] = 29; y_low[2] = 22; y_low[3] = 25; y_low[4] = 26;
	y_low[5] = 26; y_low[6] = 27;

	// configure right and top axis to show ticks but no labels:
	// (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
	// 上边框显示为虚线
	plot_->xAxis2->setVisible(false);
	plot_->xAxis2->setTickLabels(true);

	// 左边框显示为虚线
	plot_->yAxis2->setVisible(false);
	plot_->yAxis2->setTickLabels(true);

	// make left and bottom axes always transfer their ranges to right and top axes:
	connect(plot_->xAxis, SIGNAL(rangeChanged(QCPRange)), plot_->xAxis2, SLOT(setRange(QCPRange)));
	connect(plot_->yAxis, SIGNAL(rangeChanged(QCPRange)), plot_->yAxis2, SLOT(setRange(QCPRange)));
	// pass data points to graphs:
	plot_->graph(0)->setData(x, y);

	plot_->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1.5), QBrush(Qt::white), 9));
	plot_->graph(0)->setPen(QPen(QColor(255, 0, 0), 2));

	plot_->graph(1)->setData(x_low, y_low);

	plot_->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1.5), QBrush(Qt::white), 9));
	plot_->graph(1)->setPen(QPen(QColor(0, 255, 0), 2));

	// let the ranges scale themselves so graph 0 fits perfectly in the visible area:
	plot_->graph(0)->rescaleAxes();
	// same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
	plot_->graph(1)->rescaleAxes(true);

	plot_->graph(0)->setName("the tendency of temperature");//曲线名称

	// 坐标范围
	plot_->xAxis->setRange(1, 7);
	plot_->yAxis->setRange(-20, 50);

	plot_->xAxis->setLabel("week");
	plot_->yAxis->setLabel("temperature");

	plot_->xAxis->grid()->setZeroLinePen(Qt::NoPen);
	plot_->yAxis->grid()->setZeroLinePen(Qt::NoPen);

	plot_->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
	plot_->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);

	/*
	plot_->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
	plot_->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
	plot_->xAxis->grid()->setSubGridVisible(true);
	plot_->yAxis->grid()->setSubGridVisible(true);
	*/

	/* 背景色
	QLinearGradient plotGradient;
	plotGradient.setStart(0, 0);
	plotGradient.setFinalStop(0, 350);
	plotGradient.setColorAt(0, QColor(80, 80, 80));
	plotGradient.setColorAt(1, QColor(50, 50, 50));
	plot_->setBackground(plotGradient);
	*/

	// Note: we could have also just called customPlot->rescaleAxes(); instead
	// Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
	//plot_->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

}

void WaterWidget::paintRealTimeWater()
{
	//demoName = "Real Time Data Demo";

	// include this section to fully disable antialiasing for higher performance:
	/*
	customPlot->setNotAntialiasedElements(QCP::aeAll);
	QFont font;
	font.setStyleStrategy(QFont::NoAntialias);
	customPlot->xAxis->setTickLabelFont(font);
	customPlot->yAxis->setTickLabelFont(font);
	customPlot->legend->setFont(font);
	*/
	plot_->addGraph(); // blue line
	plot_->graph(0)->setPen(QPen(QColor(40, 110, 255)));
	//plot_->addGraph(); // red line
	//plot_->graph(1)->setPen(QPen(QColor(255, 110, 40)));

	QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
	timeTicker->setTimeFormat("%h:%m:%s");
	plot_->xAxis->setTicker(timeTicker);

	plot_->axisRect()->setupFullAxesBox(true);
	plot_->yAxis->setRange(-1.2, 1.2);

	plot_->xAxis2->setVisible(true);
	// 显示刻度
	plot_->xAxis2->setTickLabels(false); 

	plot_->yAxis2->setVisible(true);
	// 显示刻度
	plot_->yAxis2->setTickLabels(false);

	// make left and bottom axes transfer their ranges to right and top axes:
	connect(plot_->xAxis, SIGNAL(rangeChanged(QCPRange)), plot_->xAxis2, SLOT(setRange(QCPRange)));
	connect(plot_->yAxis, SIGNAL(rangeChanged(QCPRange)), plot_->yAxis2, SLOT(setRange(QCPRange)));

	// setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
	connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
	dataTimer.start(1000); // Interval 0 means to refresh as fast as possible
}

void WaterWidget::realtimeDataSlot()
{
	static QTime time(QTime::currentTime());
	// calculate two new data points:
	double key = time.elapsed() / 1000.0; // time elapsed since start of demo, in seconds
	static double lastPointKey = 0;
	if (key - lastPointKey > 0.002) // at most add point every 2 ms
	{
		// add data to lines:
		plot_->graph(0)->addData(key, qSin(key) + qrand() / (double)RAND_MAX * 1 * qSin(key / 0.3843));
		//plot_->graph(0)->addData(key, key);

		//plot_->graph(1)->addData(key, qCos(key) + qrand() / (double)RAND_MAX*0.5*qSin(key / 0.4364));
		
		// rescale value (vertical) axis to fit the current data:
		//ui->customPlot->graph(0)->rescaleValueAxis();
		//ui->customPlot->graph(1)->rescaleValueAxis(true);
		lastPointKey = key;
	}
	// make key axis range scroll with the data (at a constant range size of 8):
	plot_->xAxis->setRange(key, 8, Qt::AlignRight);
	//qDebug() << "key:" << key;
	plot_->replot();

	/*
	// calculate frames per second:
	static double lastFpsKey;
	static int frameCount;
	++frameCount;
	if (key - lastFpsKey > 2) // average fps over 2 seconds
	{		
		ui->statusBar->showMessage(
			QString("%1 FPS, Total Data points: %2")
			.arg(frameCount / (key - lastFpsKey), 0, 'f', 0)
			.arg(ui->customPlot->graph(0)->data()->size() + ui->customPlot->graph(1)->data()->size())
			, 0);
		
		lastFpsKey = key;
		frameCount = 0;
	}
	*/
		
	lock_realtime_data_.lockForRead();
	for (auto iter = map_realtime_data_.begin(); iter != map_realtime_data_.end(); ++iter)
	{
		//QString qstr = QString::fromStdString(iter->second);
		//double val = qstr.toDouble();
		qDebug() << "read key:" << iter->first.c_str() << ", val:" << iter->second.c_str();
	}
	lock_realtime_data_.unlock();
	
}


void WaterWidget::translateLanguage()
{
//	suggest_label->setText(tr("suggest"));
	system_safe_label->setText(tr(" Weather trends for the past seven days"));
//	power_button->setText(tr("power1"));

	login_button->setText(tr("login home"));
	info_label->setText(tr("show beautifull icon"));
	register_button->setText(tr("register"));
	privilege_label->setText(tr("privilege power"));

	fireproof_button->setText(tr("fireproof"));
	triggerman_button->setText(tr("triggerman"));
	net_shop_button->setText(tr("net shop"));

	function_label->setText(tr("function"));
	more_button->setText(tr("more"));
	button_list.at(0)->setText(tr("recovery1"));
	button_list.at(1)->setText(tr("mobile2"));
	button_list.at(2)->setText(tr("game box3"));
	button_list.at(3)->setText(tr("desktop4"));
	button_list.at(4)->setText(tr("net repair5"));
	button_list.at(5)->setText(tr("auto run6"));
	button_list.at(6)->setText(tr("net speed7"));
	button_list.at(7)->setText(tr("net pretext8"));
	button_list.at(8)->setText(tr("first add9"));

	connect_label->setText(tr("connect success"));
	version_label->setText(tr("version"));
}

bool WaterWidget::eventFilter(QObject *obj, QEvent *event)
{
	if (obj == line_label_1 || obj == line_label_2)
	{
		if (event->type() == QEvent::Paint)
		{
			int label_height_1 = line_label_1->height();
			int label_width_1 = line_label_1->width();
			QPainter painter(line_label_1);
			painter.setPen(QPen(QColor(220, 220, 220), 1, Qt::DashLine));
			painter.drawLine(label_width_1 / 2, 0, label_width_1 / 2, label_height_1);

			int label_height_2 = line_label_2->height();
			int label_width_2 = line_label_2->width();
			QPainter painter2(line_label_2);
			painter2.setPen(QPen(QColor(220, 220, 220), 1, Qt::DashLine));
			painter2.drawLine(label_width_2 / 2, 0, label_width_2 / 2, label_height_2);
		}
	}

	return QWidget::eventFilter(obj, event);
}