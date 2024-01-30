#pragma once
#include <QObject>
#include <keyevent.h>
#include <qhash.h>
//class ISoundProducer
//{
//public:
//	virtual bool produceSound(int role, int code) = 0;
//	virtual QHash<int, QString> roles() const = 0;
//
//};
class IPeriodSoundProducer /*: public ISoundProducer*/
{
public:
	enum Roles
	{
		Break,
		Work,
		Final,
		Stopped	
	};
	virtual bool produceSound(Roles role, int code ) = 0;
	virtual QList<int> availableCodes(Roles role) const = 0;
	virtual ~IPeriodSoundProducer() {}
};
class IKBSoundProducer :/* public ISoundProducer*/
{
public:
	enum InteractionType
	{
		Press,
		Release
	};
	virtual bool produceSound(Qt::Key, InteractionType, int code) = 0;
	virtual QList<Qt::Key> availableKeys() const = 0;
	virtual ~IKBSoundProducer() {}
};