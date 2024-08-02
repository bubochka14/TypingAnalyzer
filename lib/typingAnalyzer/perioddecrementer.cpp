#include "perioddecrementer.h"
PeriodDecrementer::PeriodDecrementer(PeriodsModel* model, QObject* parent)
	:Executable(parent)
	,_interval(1000)
	,_model(model)
	,_activeIndex(0)
{
	connect(&_timer, &QTimer::timeout, this, &PeriodDecrementer::decrement);
	connect(this, &PeriodDecrementer::newPeriod, &PeriodDecrementer::onNewPeriod);
	connect(this, &PeriodDecrementer::periodCompleted, &PeriodDecrementer::onPeriodCompleted);
}
uint PeriodDecrementer::decrementInterval() const { return _interval; }
void PeriodDecrementer::setDecrementInterval(uint other)
{
	if (_interval == other)
		return;
	_interval = other;
	emit decrementIntervalChanged();
	if (state() == Started)
	{
		_timer.stop();
		_timer.start(_interval);
	}
}
void PeriodDecrementer::start()
{
	_timer.start(_interval);
	_model->setData(_model->index(activeIndex()), PeriodsModel::Active, PeriodsModel::PeriodState);
	Executable::start();
}
void PeriodDecrementer::stop()
{
	_timer.stop();
	Executable::stop();
}

void PeriodDecrementer::resetModel() {
	for (size_t i = 0; i < _model->rowCount(); i++)
	{
        _model->setData(_model->index(i, 0), PeriodsModel::Inactive, PeriodsModel::PeriodState);
		_model->setData(_model->index(i, 0), _model->data(_model->index(i,0),PeriodsModel::Duration), PeriodsModel::RemainingTime);
	}
}
void PeriodDecrementer::onNewPeriod()
{
	_model->setData(_model->index(activeIndex()), PeriodsModel::Active, PeriodsModel::PeriodState);
}
void PeriodDecrementer::onPeriodCompleted()
{
	_model->setData(_model->index(activeIndex()), PeriodsModel::Completed, PeriodsModel::PeriodState);
}
void PeriodDecrementer::decrement()
{
	qint64 remTime = 0; PeriodsModel::PeriodStates currentPeriod = PeriodsModel::Completed;
	//iterate through elements until not completed period is found 
	while(activeIndex() < _model->rowCount())
	{
		currentPeriod = _model->data(_model->index(activeIndex()),
			PeriodsModel::PeriodState).value< PeriodsModel::PeriodStates>();
		if(currentPeriod != PeriodsModel::Completed)
			break;
		setActiveIndex(activeIndex() + 1);
	}
	if (activeIndex() == _model->rowCount())
		stop();
	if(currentPeriod==PeriodsModel::Inactive)
		emit newPeriod();

	remTime = _model->data(_model->index(activeIndex()), PeriodsModel::RemainingTime).toLongLong();
	//decrement remainingTime
	remTime = ((remTime >= _interval) ? (remTime - _interval) : 0);
	//set decremented time to model
    _model->setData(_model->index(activeIndex()), remTime, PeriodsModel::RemainingTime);
	// if current section has just closed
	if(remTime <=0){
		emit periodCompleted();
	}

}
quint32 PeriodDecrementer::activeIndex() const
{
	return _activeIndex;
}
void PeriodDecrementer::finish()
{
	_timer.stop();
	resetModel();
	setActiveIndex(0);
	Executable::finish();
}
void PeriodDecrementer::setActiveIndex(quint32 other)
{
	if (_activeIndex == other)
		return;
	_activeIndex = other;
	emit activeIndexChanged();
}
