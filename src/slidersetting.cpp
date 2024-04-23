#include "slidersetting.h"
SliderSetting::SliderSetting(const QString& name, QObject* parent)
	:AbstractAppSetting(name, parent)
	,_min(0)
	,_max(100)
	,_content(0)
	,_engine(new QQmlEngine(this))
{}
bool SliderSetting::setValue(const QVariant& other)
{
	if (!other.canConvert<quint64>() || _value == other.value<quint64>())
		return false;
	if(_value != other.value<quint64>()){
		_value = other.value<quint64>();
		_content->setProperty("value", _value);
		emit valueChanged();
	}

}
QVariant SliderSetting::value() const
{
	return _value;
}
int SliderSetting::min() const
{
	return _min;
}
int SliderSetting::max() const
{
	return _max;
}
void SliderSetting::setMin(int other)
{
	if(other != _min){
		_min = other;
		_content->setProperty("from", _min);
		emit minChanged();
	}
}
void SliderSetting::setMax(int other)
{
	_max = other;
	_content->setProperty("to", _max);
	emit maxChanged();
}
QQuickItem* SliderSetting::getContent()
{
	if (!_content)
	{
		ContentBuilder builder(QUrl("qrc:/components/ui/UISlider.qml"), _engine);
		builder.addContextPointer("listSetting", (QObject*)this);
		_content = builder.build();
		connect(_content, SIGNAL(valueChanged()), this, SLOT(handleValueChange()));
	}
	return _content;
}
void SliderSetting::handleValueChange()
{
	_value = _content->property("value").toInt();
	emit valueChanged();
}
