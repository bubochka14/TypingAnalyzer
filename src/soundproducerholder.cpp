#include "soundproducerholder.h"
KBSProducerHolder::KBSProducerHolder(QObject* parent)
	: QObject(parent)
{
	bindableCurrentProducer().setBinding([&]() {return _hash.contains(_name) ? _hash.value(_name) : nullptr; });
	setDefaultName();
}
QString KBSProducerHolder::currentName() const
{
	return _name;
}
void  KBSProducerHolder::setDefaultName()
{
	_name = "<none>";
}
QBindable<IKBSoundProducer*> KBSProducerHolder::bindableCurrentProducer()
{
	return &_currentProducer;
}
QStringList KBSProducerHolder::names() const
{
	return _hash.keys();
}
IKBSoundProducer* KBSProducerHolder::currentProducer() const
{
	return _currentProducer.value();
}

void KBSProducerHolder::add(QString name, IKBSoundProducer* pr)
{
	if(!_hash.contains(name))
	{
		_hash.insert(name, pr);
		emit namesChanged();
	}
}
void KBSProducerHolder::set(const QString& name)
{
	if(_name != name)
	{
		if (!_hash.contains(name))
			return;
		_name = name;
		emit currentNameChanged();
	}
}

PeriodSProducerHolder::PeriodSProducerHolder(QObject* parent)
	: QObject(parent)
{
	bindableCurrentProducer().setBinding([&]() {return _hash.contains(_name) ? _hash.value(_name) : nullptr; });
	setDefaultName();
}
QString PeriodSProducerHolder::currentName() const
{
	return _name;
}
void PeriodSProducerHolder::setDefaultName()
{
	_name = "<none>";
}
QStringList PeriodSProducerHolder::names() const
{
	return _hash.keys();

}
IPeriodSoundProducer* PeriodSProducerHolder::currentProducer() const
{
	return _currentProducer.value();
}
void PeriodSProducerHolder::add(QString name, IPeriodSoundProducer* pr)
{
	if (!_hash.contains(name))
	{
		_hash.insert(name, pr);
		emit namesChanged();
	}
}
void PeriodSProducerHolder::set(const QString& name)
{
	if (_name != name)
	{
		if (!_hash.contains(name))
			return;
		_name = name;
		emit currentNameChanged();
	}
}

QBindable<IPeriodSoundProducer*> PeriodSProducerHolder::bindableCurrentProducer()
{
	return &_currentProducer;
}