#pragma once
#include "apppage.h"
#include "appsetting.h"
#include <qqmlengine.h>
#include "contentbuilder.h"
class SettingsPage : public AppPage
{
	Q_OBJECT;
	Q_PROPERTY(QList<AbstractAppSetting*> settings READ settings NOTIFY settingsChanged)
public:
    explicit SettingsPage(QQmlEngine* e, QObject* parent = nullptr);
	QQuickItem* getContent() override;
	void addSetting(AbstractAppSetting* s);
	QList<AbstractAppSetting*> settings() const;
signals:
	void settingsChanged();
private:
	QQuickItem* _content;
	QQmlEngine* _engine;
	QList<AbstractAppSetting*> _settings;
};
