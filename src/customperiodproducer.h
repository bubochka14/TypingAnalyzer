#pragma once
#include "aconfigurable.h"
#include "soundinterfaces.h"
#include <qrandom.h>
#include <QObject>
#include <qsoundeffect.h>
class CustomPeriodProducer : public QObject, IConfigurable, IPeriodSoundProducer
{
	Q_OBJECT;
	Q_INTERFACES(IPeriodSoundProducer)
	Q_INTERFACES(IConfigurable)
public:
	explicit CustomPeriodProducer(QObject* parent = nullptr);
	bool produceSound(const PeriodInfo&) override;
	void addUniversalSound(const QList<QUrl>& list);
	void setSounds(const PeriodInfo&, const QList<QUrl>& list);
	Config* config() const override;
	void setConfig(Config*) override;
private:
	QHash<PeriodInfo, QList<QSoundEffect*>> _sounds;
};