/*
 * main
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "drop_shadow_widget.h"
#include "system_tray.h"
#include "about_us.h"
#include "title_widget.h"
#include "content_widget.h"
#include "kill_mummy_widget.h"
#include "setting_dialog.h"
#include "character_widget.h"
#include "login_dialog.h"
#include "register_widget.h"
#include "main_menu.h"
#include "skin_widget.h"
#include "temperature_widget.h"
#include "water_widget.h"

// get data from redis
//#include "redis_server.h"

//#include <QMainWindow>
#include <QTranslator>
#include <QDesktopWidget>
#include <QLocalSocket>
#include <QLocalServer>
#include <QStackedWidget>

class MainWidget : public DropShadowWidget
{
    Q_OBJECT

public:

    MainWidget(QWidget *parent = 0);
    ~MainWidget();
	void setTranslator(QTranslator* translator);
	bool isRunning(); 

protected:

    virtual void paintEvent(QPaintEvent *event);

public slots:

	void showWidget();

private slots:

	void newLocalConnection();  

	void showSkinWidget();
	void showMainMenu();
	void showSettingDialog();
	void showAboutUs();
	void showNewCharacter();
	void showLoginDialog();
	void showRegisterDialog();
	void changeSkin(QString skin_name);
	void iconIsActived(QSystemTrayIcon::ActivationReason reason);
	void changeLanguage(LANGUAGE language);

	void turnPage(int current_page);

private:

	void initLocalConnection();

    void startThread();

private:

	QStackedWidget *statked_widget;
    TitleWidget *title_widget; //title bar, include many buttons

    ContentWidget *content_widget; //main content
    KillMummyWidget *kill_mummy_widget;  //
    TemperatureWidget* m_temperature_widget_;//temperature
	WaterWidget* m_water_widget_;	// ˮ

    SystemTray *system_tray; //
    SettingDialog *setting_dialog; //
    CharacterWidget *character_widget; //
    AboutUsDialog *about_us_dialog; //
    LoginDialog *login_dialog; //
    RegisterWidget *register_widget; //
    QString skin_name;//
    MainMenu *main_menu; //
    SkinWidget *skin_widget; //

    QTranslator* translator; //
    LANGUAGE current_language; //

	QLocalServer *server;  
    bool is_running;

    //RedisServer redis_server_;

};

#endif // MAINWINDOW_H
