#include "pageapplication.h"
Q_LOGGING_CATEGORY(LC_APP, "app");
PageApplication::PageApplication(int argc, char**argv)
	:_qApp(argc, argv)
	,_engine(new QQmlApplicationEngine(this))
{
	setKbProd(qobject_cast<IKBSoundProducer*>(new TypeWriterSP(this)));
    addPage(new TimeFocusPage(this, _engine,this));
    addPage(new FreeModePage(this, _engine, this));
	setupSettings();
	_qApp.setQuitOnLastWindowClosed(false);
    connect(_engine,&QQmlEngine::quit,&_qApp,&QApplication::quit);
}
void PageApplication::addPage(AppPage* other)
{
	_pages.append(other);
	emit pagesChanged(); 
}
bool PageApplication::removePage(size_t index)
{
	if (index >= _pages.size())
		return false;
	_pages.remove(index);
	emit pagesChanged();
}
void PageApplication::setupSettings()
{	

	SettingsPage* sPage = new SettingsPage(_engine, this);
	ListSetting* kbSett = new ListSetting(tr("Keyboard sounds"), this);
	kbSett->addOption(tr("Typewriter"), QVariant::fromValue((IKBSoundProducer*)new TypeWriterSP(this)));
	connect(kbSett, &AbstractAppSetting::valueChanged, this, [=]() {
		setKbProd((IKBSoundProducer*)kbSett->value().value<IKBSoundProducer*>());
		});
	sPage->addSetting(kbSett, "General");

	SliderSetting* sliderSett = new SliderSetting("Keyboard sounds volume", this);
	sliderSett->setValue(kbProd()->volume() * sliderSett->max());
	connect(sliderSett, &SliderSetting::valueChanged, this, [=]()
	{
		if (sliderSett->value().canConvert<double>())
			kbProd()->setVolume(sliderSett->value().value<double>());
	});
	sPage->addSetting(sliderSett, "General");
	for (auto& p : _pages)
	{
		for (auto& s : p->settings())
		{
			sPage->addSetting(s,p->name());
		}
	}
	addPage(sPage);
}
QList<AppPage*> PageApplication::pages() const
{
	return _pages;
}

int PageApplication::exec()
{
	ContentBuilder builder(_engine);
	builder.addContextPointer("app", this);
	builder.build(LIB_NAME, "Main");
	return _qApp.exec();
}
