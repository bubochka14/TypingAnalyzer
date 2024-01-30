#pragma once
#include <QObject>
#include <qapplication.h>
#include <qqmlapplicationengine.h>
#include "applicationsettings.h"
#include "soundproducerholder.h"
#include "emptyperiodsoundproducer.h"
#include "typewritersp.h"
#include "aconfigloader.h"
#include "localconfigloader.h"
#include "emptykbsoundproducer.h"
class App : public QObject
{
	Q_OBJECT;
public:
	explicit App(int argc, char** argv);
	int exec();
protected:
	virtual void fillSPHolders();
private:
	QApplication _qApp;
	ApplicationSettings _settings;
	KBSProducerHolder _kbspHolder;
	PeriodSProducerHolder _pspHolder;
	AConfigLoader* _configLoader;
};