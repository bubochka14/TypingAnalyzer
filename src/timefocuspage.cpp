#include "timefocuspage.h"
TimeFocusPage::TimeFocusPage(Application* app, QQmlEngine* e, QObject* parent)
	:ExecutableAppPage("Time Focus", parent)
	,_content(nullptr)
    ,_app(app)
	,_engine(e)
	,_model(new TimeFocusModel(this))
	,_periodProdSetting(new ListSetting("Period Sounds"))
{
	CustomPeriodProducer* ringProd = new CustomPeriodProducer(this);
	ringProd->addUniversalSound(QList<QUrl>() << QUrl("qrc:/sounds/ring.wav"));
	_periodProdSetting->addOption("Ring", QVariant::fromValue((IPeriodSoundProducer*)ringProd));
	_ex = new TimeFocusExecutable(_model, app->kbProd(), _periodProdSetting->value().value<IPeriodSoundProducer*>(), this);
	connect(_periodProdSetting, &AbstractAppSetting::valueChanged, this, [=]() {
		_ex->setPeriodProducer(_periodProdSetting->value().value<IPeriodSoundProducer*>());
		});
	connect(_app, &Application::kbProdChanged, this, [=]() {_ex->setKbProd(_app->kbProd()); });
	setIconSource(QUrl("qrc:/components/pics/coffee"));
}
Executable* TimeFocusPage::executable() const
{
	return _ex;
}
void TimeFocusPage::setModel(TimeFocusModel* other)
{
	_model = other;
}
TimeFocusModel* TimeFocusPage::model() const
{
	return _model;
}
QQuickItem* TimeFocusPage::getContent()
{
	if (!_content)
	{
		ContentBuilder builder(QUrl("qrc:/components/TimeFocusPage.qml"), _engine);
		builder.addContextPointer("timeFocusPage", this);
		_content = builder.build();
	}
	return _content;
}
QList<AbstractAppSetting*> TimeFocusPage::settings() const
{
	return QList<AbstractAppSetting*>()<< _periodProdSetting << _volume;
}
quint16 TimeFocusPage::activeIndex() const
{
	return _ex->topIndex();
}