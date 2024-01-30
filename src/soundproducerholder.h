#pragma once
#include <QObject>
#include <QHash>
#include <QProperty>
#include "soundinterfaces.h"
class KBSProducerHolder : public QObject
{
	Q_OBJECT;
	Q_PROPERTY(QString currentName READ currentName NOTIFY currentNameChanged);
	Q_PROPERTY(QStringList names READ names NOTIFY namesChanged);
	Q_PROPERTY(IKBSoundProducer* currentProducer READ currentProducer NOTIFY currentProducerChanged BINDABLE bindableCurrentProducer);

public:
	explicit KBSProducerHolder(QObject* parent = nullptr);
	QString currentName() const;
	QStringList names() const;
	//returns nullptr if prod wasn`t found
	IKBSoundProducer* currentProducer() const;

	void add(QString name, IKBSoundProducer* pr);
	void set(const QString& name);
signals:
	void currentNameChanged();
	void currentProducerChanged();
	void namesChanged();
protected:
	virtual void setDefaultName();
	QBindable<IKBSoundProducer*> bindableCurrentProducer();
private:
	QHash<QString, IKBSoundProducer*> _hash;
	QString _name;
	Q_OBJECT_BINDABLE_PROPERTY(KBSProducerHolder, IKBSoundProducer*, _currentProducer, &KBSProducerHolder::currentProducerChanged);


};
class PeriodSProducerHolder : public QObject
{
	Q_OBJECT;
	Q_PROPERTY(QString currentName READ currentName NOTIFY currentName);
	Q_PROPERTY(QStringList names READ names NOTIFY currentName);
	Q_PROPERTY(IPeriodSoundProducer* currentProducer READ currentProducer NOTIFY currentProducerChanged BINDABLE bindableCurrentProducer);

public:
	explicit PeriodSProducerHolder(QObject* parent = nullptr);
	QString currentName() const;
	QStringList names() const;
	//returns nullptr if prod wasn`t found
	IPeriodSoundProducer* currentProducer() const;

	void add(QString name, IPeriodSoundProducer* pr);
	void set(const QString& name);
signals:
	void currentNameChanged();
	void currentProducerChanged();
	void namesChanged();
protected:
	virtual void setDefaultName();
	QBindable<IPeriodSoundProducer*> bindableCurrentProducer();

private:
	QHash<QString, IPeriodSoundProducer*> _hash;
	QString _name;
	Q_OBJECT_BINDABLE_PROPERTY(PeriodSProducerHolder, IPeriodSoundProducer*, _currentProducer, &PeriodSProducerHolder::currentProducerChanged);

};