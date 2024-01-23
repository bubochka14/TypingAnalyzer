#pragma once
#include <QObject>
#include <keyevent.h>
class IPeriodSoundProducer 
{
public:
	enum Roles
	{
		Break,
		Work,
		Final
	};
	virtual bool produceSound(Roles role, int code ) = 0;
	virtual QList<int> availableCodes(Roles role) const = 0;
	virtual ~IPeriodSoundProducer() {}
};
class IKBSoundProducer 
{
public:
	virtual bool produceSound(const KeyEvent& e) = 0;
	virtual QList<Qt::Key> availableKeys() const = 0;
	virtual ~IKBSoundProducer() {}
};