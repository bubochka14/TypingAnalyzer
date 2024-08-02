#pragma once
#include <QObject>
#include "periodsmodel.h"
#include "executable.h"
#include "soundinterfaces.h"
#include "typingmeter.h"
#include "executablekbproducer.h"
#include "typinganalyzer_include.h"

class TP_EXPORT PeriodDecrementer : public Executable
{
	Q_OBJECT;
	Q_PROPERTY(quint32 decrementInterval READ decrementInterval WRITE setDecrementInterval NOTIFY decrementIntervalChanged);
	Q_PROPERTY(quint16 activeIndex READ activeIndex NOTIFY activeIndexChanged)
public:
    explicit PeriodDecrementer(PeriodsModel* model,QObject* parent = nullptr);
	uint decrementInterval() const;
	quint32 activeIndex() const;
	void setDecrementInterval(uint other);
	void resetModel();  
public slots:
	void start() override;
	void finish() override;
	void stop() override;
signals:
	void newPeriod();
	void periodCompleted();
	void decrementIntervalChanged();
	void activeIndexChanged();
protected slots:
	void decrement();
	void onNewPeriod();
	void onPeriodCompleted();
protected:
	void setActiveIndex(quint32 other);
private:
	QTimer _timer;
	quint32 _interval;
    PeriodsModel* _model;
	quint32 _activeIndex;
};
