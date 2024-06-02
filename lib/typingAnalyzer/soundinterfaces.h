#pragma once
#include <QObject>
#include <keyevent.h>
#include <qqmlengine.h>
#include "typinganalyzer_include.h"

struct TP_EXPORT PeriodInfo
{
	Q_GADGET;
	QML_ELEMENT;
public:
	
	enum PeriodType
	{

		Break,
		Work,
		Final,
		Stopped
	}; Q_ENUM(PeriodType)
		PeriodType type;
	PeriodInfo(PeriodType t= Stopped);
};
uint qHash(const PeriodInfo& item);
bool operator==(const PeriodInfo& p1, const PeriodInfo& p2);
class TP_EXPORT IPeriodSoundProducer
{
public:

	virtual bool produceSound(const PeriodInfo&) = 0;
	virtual void setVolume(double other) = 0;
	virtual double volume() const = 0;
	virtual ~IPeriodSoundProducer() {}
};
Q_DECLARE_INTERFACE(IPeriodSoundProducer,"Period sound producer interface")
Q_DECLARE_METATYPE(IPeriodSoundProducer*)
class TP_EXPORT IKBSoundProducer
{
public:
	virtual bool produceSound(const KeyEvent&) = 0;
	virtual void setVolume(double other) = 0;
	virtual double volume() const = 0;
	virtual ~IKBSoundProducer() {}
};

Q_DECLARE_INTERFACE(IKBSoundProducer,"Keyboard sound producer interface")
Q_DECLARE_METATYPE(IKBSoundProducer*)
