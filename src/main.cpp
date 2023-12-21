
#include "KeyboardAnalyzer.h"
#include <cstdio>
#include <QApplication>
#include <qkeysequence.h>
#include "KeyboardInterceptor.h"
#include "typewritersp.h"
#include "qqmlapplicationengine.h"
#include <qdir>
using namespace std;
int main(int argc, char**argv)
{
	QApplication app(argc, argv);
	app.setQuitOnLastWindowClosed(false);

	//KeyboardInterceptor w;
	TypeWriterSP t;
	//QObject::connect(&w, &KeyboardInterceptor::eventProduced, [&](KeyEvent e) {qDebug() << e.key << e.modifiers << e.text; t.produceSound(e); });

    QQmlApplicationEngine e(":/components/Main.qml");
	int exit = app.exec();
	return exit;
}
