#pragma once	
#include "apppage.h"
#include "displayedsetting.h"
#include <qqmlengine.h>
#include "contentbuilder.h"
#include "typinganalyzer_include.h"

class TP_EXPORT SettingsPage : public AppPage
{
	Q_OBJECT;
	Q_PROPERTY(QStringList headers READ headers NOTIFY headersChanged);

public:
	explicit SettingsPage(QQmlEngine* e, QObject* parent = nullptr);
	QQuickItem* getContent() override;
	void addSetting(DisplayedSetting* s, const QString& header);
	Q_INVOKABLE QList<DisplayedSetting*> addedSettings(const QString& header) const;//AppPage settings() name conflict
	QStringList headers() const;
signals:
//	void addedSettingsChanged();
	void headersChanged();
private:
	QQuickItem* _content;
	QQmlEngine* _engine;
	QStringList _headers;
	QHash<QString,QList<DisplayedSetting*>> _addedSettings;
};
