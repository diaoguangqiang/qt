#include "main_widget.h"
#include <QtWidgets/QApplication>

#include <QTextCodec>
#include <QSharedMemory>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QTextCodec::setCodecForLocale(QTextCodec::codecForName("system"));

	QTranslator translator;
	translator.load(QString(":/qm/qt_zh_CN"));
	app.installTranslator(&translator);

	QTranslator translator_zh;
	translator_zh.load(QString(":/qm/360safe_zh"));
	app.installTranslator(&translator_zh);

	//
	QFile qss(":/qss/360safe");
	qss.open(QFile::ReadOnly);
	qApp->setStyleSheet(qss.readAll());
	qss.close();

	QSharedMemory shared_memory;
	shared_memory.setKey(QString("main_window"));

	if (shared_memory.attach())
	{
		return 0;
	}

	if (shared_memory.create(1))
	{
		MainWidget main_widget;
		main_widget.setTranslator(&translator_zh);
		main_widget.showWidget();
		main_widget.show();

		return app.exec();
	}

// 	farmer w;
// 	w.show();
// 	return a.exec();
}
