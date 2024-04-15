#pragma once
#include "apppage.h"
#include "timefocusexecutable.h"
#include "contentbuilder.h"
#include "timefocusmodel.h"
#include <qquickitem.h>
#include "typewritersp.h"
#include "soundinterfaces.h"
#include "customperiodproducer.h"
#include "listsetting.h"
#include <qquickitem.h>
#include "application.h"
class TimeFocusPage : public ExecutableAppPage
{
	Q_OBJECT;
	Q_PROPERTY(TimeFocusModel* model READ model NOTIFY modelChanged);
public:
    explicit TimeFocusPage(Application* app, QQmlEngine* e, QObject* parent=nullptr);
	void setModel(TimeFocusModel*);
	TimeFocusModel* model() const;
	Executable* executable() const override;
	QQuickItem* getContent() override;
	QList<AbstractAppSetting*> settings() const override;


signals:
	void modelChanged();
private:
	TimeFocusModel* _model;
	TimeFocusExecutable* _ex;
	QQuickItem* _content;
    Application* _app;
	QQmlEngine* _engine;
	ListSetting* _periodProdSetting;
};
