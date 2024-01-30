#include "app.h"
App::App(int argc, char**argv)
	:_qApp(argc, argv)
	,_configLoader(new LocalConfigLoader)
{
	fillSPHolders();
	_qApp.setQuitOnLastWindowClosed(false);
}
void App::fillSPHolders()
{
	_kbspHolder.add(tr("empty"), new EmptyKBSoundPlayer(this));
	_kbspHolder.add(tr("typewriter"), new TypeWriterSP(this));
	_pspHolder.add(tr("empty"), new EmptyPeriodSoundProducer(this));

}
int App::exec()
{
	//todo: qmlengine error handling 
	QQmlApplicationEngine e(":/components/Main.qml");
	return true;
}