
#include "KeyboardAnalyzer.h"
#include <cstdio>
#include <QApplication>
#include <qkeysequence.h>
#include "KeyboardInterceptor.h"
#include "applicationsettings.h"
#include "typewritersp.h"
#include "qqmlapplicationengine.h"
#include <qdir>
using namespace std;
int main(int argc, char**argv)
{
	QApplication app(argc, argv);
	app.setQuitOnLastWindowClosed(false);
	ApplicationSettings sett;
	qDebug() << sett.KBSoundProducerName();
	sett.setKBSoundProducerName("a");
	qDebug() << sett.KBSoundProducerName();
    QQmlApplicationEngine e(":/components/Main.qml");
	TypeWriterSP s;
	int exit = app.exec();
	return exit;
}
