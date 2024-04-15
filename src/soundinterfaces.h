#pragma once
#include <QObject>
#include <keyevent.h>
#include <qqmlengine.h>
struct  PeriodInfo
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
class IPeriodSoundProducer /*: public virtual QObject*/
{
	//Q_OBJECT;

public:

	virtual bool produceSound(const PeriodInfo&) = 0;
	virtual ~IPeriodSoundProducer() {}
//protected:
//	explicit IPeriodSoundProducer(QObject* parent) : QObject(parent) {}
};
Q_DECLARE_INTERFACE(IPeriodSoundProducer,"Period sound producer interface")
Q_DECLARE_METATYPE(IPeriodSoundProducer*)
class IKBSoundProducer //: public QObject
{
	//Q_OBJECT;

public:
	virtual bool produceSound(const KeyEvent&) = 0;
	virtual ~IKBSoundProducer() {}
//protected:
	//explicit IKBSoundProducer(QObject* parent) : QObject(parent) {}
};

Q_DECLARE_INTERFACE(IKBSoundProducer,"Keyboard sound producer interface")
Q_DECLARE_METATYPE(IKBSoundProducer*)
