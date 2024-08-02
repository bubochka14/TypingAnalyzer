#include "timefocuspage.h"
TimeFocusPage::TimeFocusPage(Application* app, QQmlEngine* e, QObject* parent)
	:ExecutableAppPage("Time Focus", parent)
	, _content(nullptr)
	, _app(app)
	, _engine(e)
	, _model(new PeriodsModel(this))
	, _periodProdSetting(new ListSetting("Period Sounds"))
	, _volumeSetting(new SliderSetting("Periods volume", this))
{
	CustomPeriodProducer* ringProd = new CustomPeriodProducer(this);
    ringProd->addUniversalSound(QList<QUrl>() << QUrl("qrc:/sounds/ring.wav"));
	_periodProdSetting->addOption("Ring", QVariant::fromValue((IPeriodSoundProducer*)ringProd));
	_ex = new PeriodDecrementer(_model, this);
	//_volumeSetting->setValue(_ex->periodProducer()->volume() * _volumeSetting->max());

	connect(_periodProdSetting, &DisplayedSetting::valueChanged, this, [=]() {
		//_ex->setPeriodProducer(_volumeSetting->value().value<IPeriodSoundProducer*>());
		//_ex->periodProducer()->setVolume(_volumeSetting->value().value<double>()* _volumeSetting->max());
		});

	connect(_volumeSetting, &DisplayedSetting::valueChanged, this, [=]() {
		//_ex->periodProducer()->setVolume(_volumeSetting->value().value<double>() * _volumeSetting->max());
		});
	
	connect(_app, &Application::kbProdChanged, this, [=]() {/*_ex->setKbProd(_app->kbProd())*/; });
}
Executable* TimeFocusPage::executable() const
{
	return _ex;
}
void TimeFocusPage::setModel(PeriodsModel* other)
{
	if (other == _model)
		return;
	_model = other;
	emit modelChanged();
}
PeriodsModel* TimeFocusPage::model() const
{
	return _model;
}
QQuickItem* TimeFocusPage::getContent()
{
	if (!_content)
	{
		ContentBuilder builder(_engine);
		//builder.addContextPointer("timeFocusPage", this);
		builder.setInitialProperties({ { "tfAlg", QVariant::fromValue(_ex) },
			{"model",QVariant::fromValue(_model)} });
		_content = builder.build(LIB_NAME,"TimeFocusPage");
	}
	return _content;
}
QList<DisplayedSetting*> TimeFocusPage::settings() const
{
	return QList<DisplayedSetting*>()<< _periodProdSetting << _volumeSetting;
}
