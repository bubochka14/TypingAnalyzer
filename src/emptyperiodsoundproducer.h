#pragma once
#include <QObject>
#include "soundinterfaces.h"
class EmptyPeriodSoundProducer : public QObject, public IPeriodSoundProducer
{
	Q_OBJECT;
public:
	explicit EmptyPeriodSoundProducer(QObject* parent = nullptr);
	bool produceSound(Roles role, int code) override;
	QList<int> availableCodes(Roles role) const override;

};