#include "emptyperiodsoundproducer.h"
EmptyPeriodSoundProducer::EmptyPeriodSoundProducer(QObject* parent)
	:QObject(parent)
{
}
bool EmptyPeriodSoundProducer::produceSound(Roles role, int code)
{
	return true;
}
QList<int> EmptyPeriodSoundProducer::availableCodes(Roles role) const 
{
	return QList<int>();
}
