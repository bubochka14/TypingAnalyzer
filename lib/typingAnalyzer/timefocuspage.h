#pragma once
#include "apppage.h"
#include "perioddecrementer.h"
#include "contentbuilder.h"
#include "periodsmodel.h"
#include "slidersetting.h"
#include <qquickitem.h>
#include "typewritersp.h"
#include "soundinterfaces.h"
#include "customperiodproducer.h"
#include "listsetting.h"
#include <qquickitem.h>
#include "application.h"
class TP_EXPORT TimeFocusPage : public ExecutableAppPage
{
	Q_OBJECT;
	Q_PROPERTY(PeriodsModel* model READ model NOTIFY modelChanged);
public:
    explicit TimeFocusPage(Application* app, QQmlEngine* e, QObject* parent=nullptr);
	void setModel(PeriodsModel*);
	PeriodsModel* model() const;
	Executable* executable() const override;
	QQuickItem* getContent() override;
	QList<DisplayedSetting*> settings() const override;
signals:
	void modelChanged();
private:
	PeriodsModel* _model;
	PeriodDecrementer* _ex;
	QQuickItem* _content;
    Application* _app;
	QQmlEngine* _engine;
	ListSetting* _periodProdSetting;
	SliderSetting* _volumeSetting;
};
