
#include "KeyboardAnalyzer.h"
#include <cstdio>
#include <QApplication>
#include <qkeysequence.h>
#include "keywatcher.h"
#include "typewritersp.h"
#include "winkeyboardinterceptor.h"
#include "qqmlapplicationengine.h"
#include <qdir>
using namespace std;
int main(int argc, char**argv)
{
	QApplication app(argc, argv);
	KeyWatcher w;
	TypeWriterSP t;
	QObject::connect(&w, &KeyWatcher::eventProduced, [&](KeyEvent e) {qDebug() << e.key << e.modifiers << e.text; t.produceSound(e); });

    QQmlApplicationEngine e(":/components/Main.qml");
	int exit = app.exec();
	return exit;
}
